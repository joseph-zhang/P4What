import os
import torch
import numpy as np
import torchvision
from PIL import Image
import torch.nn as nn
from torchvision import transforms
import torchvision.utils as vutils
from tensorboardX import SummaryWriter
from torch.utils.data import Dataset, DataLoader
root = "./mnist/"

# ------------------------------------------------------------ Deal with Data --------------------------------------------------------------

def default_loader(path):
    return Image.open(path)
class MyDataset(Dataset):
    def __init__(self, image_dir, transform=None, target_transform=None, loader=default_loader):
        fh = open(image_dir, 'r')
        imgs = []
        for line in fh:
            line = line.strip('\n')
            line = line.rstrip()
            words = line.split()
            imgs.append((words[0],int(words[1])))
        self.imgs = imgs
        self.transform = transform
        self.target_transform = target_transform
        self.loader = loader

    def __getitem__(self, index):
        fn, label = self.imgs[index]
        img = self.loader(fn)
        if self.transform is not None:
            img = self.transform(img)
        return img, label

    def __len__(self):
        return len(self.imgs)

# Resize is introduced -- torchvision > 0.1.9
cust_transform = transforms.Compose([transforms.Resize(32),
                                     transforms.ToTensor(),
                                     transforms.Normalize(mean=([0.5]),
                                                          std=([0.5]))])

train_data = MyDataset(image_dir = root+'train.txt', transform=cust_transform)
train_loader = DataLoader(dataset=train_data, batch_size=32, shuffle=True)


# ------------------------------------------------------------ Network Definition -------------------------------------------------------------

# define Generator
class Generator(nn.Module):
    def __init__(self):
        super(Generator, self).__init__()

        self.init_size = 32 // 4
        self.l1 = nn.Sequential(nn.Linear(100, 128*self.init_size**2))

        self.conv_blocks = nn.Sequential(
            nn.BatchNorm2d(128),
            nn.Upsample(scale_factor=2),
            nn.Conv2d(128, 128, 3, stride=1, padding=1),
            nn.BatchNorm2d(128, 0.8),
            nn.LeakyReLU(0.2, inplace=True),
            nn.Upsample(scale_factor=2),
            nn.Conv2d(128, 64, 3, stride=1, padding=1),
            nn.BatchNorm2d(64, 0.8),
            nn.LeakyReLU(0.2, inplace=True),
            nn.Conv2d(64, 1, 3, stride=1, padding=1),
            nn.Tanh()
        )

    def forward(self, z):
        out = self.l1(z)
        out = out.view(out.shape[0], 128, self.init_size, self.init_size)
        img = self.conv_blocks(out)
        return img

# define Discriminator
class Discriminator(nn.Module):
    def __init__(self):
        super(Discriminator, self).__init__()

        def discriminator_block(in_filters, out_filters, bn=True):
            block = [nn.Conv2d(in_filters, out_filters, 3, 2, 1),
                     nn.LeakyReLU(0.2, inplace=True),
                     nn.Dropout2d(0.25)]
            if bn:
                block.append(nn.BatchNorm2d(out_filters, 0.8))
            return block

        self.model = nn.Sequential(
            *discriminator_block(1, 16, bn=False),
            *discriminator_block(16, 32),
            *discriminator_block(32, 64),
            *discriminator_block(64, 128),
        )

        # The height and width of downsampled image
        ds_size = 32 // 2**4
        self.adv_layer = nn.Sequential( nn.Linear(128*ds_size**2, 1),
                                        nn.Sigmoid())

    def forward(self, img):
        out = self.model(img)
        out = out.view(out.shape[0], -1)
        validity = self.adv_layer(out)

        return validity

# ----------------------------------------------------------------- Training steps --------------------------------------------------------------

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

def weights_init_normal(m):
    classname = m.__class__.__name__
    if classname.find('Conv') != -1:
        torch.nn.init.normal_(m.weight.data, 0.0, 0.02)
    elif classname.find('BatchNorm2d') != -1:
        torch.nn.init.normal_(m.weight.data, 1.0, 0.02)
        torch.nn.init.constant_(m.bias.data, 0.0)

# create summary writer
writer = SummaryWriter(log_dir='./ckpt_dir/')

Dnet = Discriminator().to(device)
Gnet = Generator().to(device)
Dnet.apply(weights_init_normal)
Gnet.apply(weights_init_normal)
print(Dnet)
print(Gnet)

criterion = nn.BCELoss()
d_optimizer = torch.optim.Adam(Dnet.parameters(), lr=0.0002)
g_optimizer = torch.optim.Adam(Gnet.parameters(), lr=0.0002)

train_iter = 0
for epoch in range(200):
    # [Alternate training] --> Gnet and Dnet
    for i, (imgs, _) in enumerate(train_loader):
        imgs = imgs.to(device)

        # Adversarial ground truths
        real_labels = torch.ones(imgs.size(0), 1).to(device)
        fake_labels = torch.zeros(imgs.size(0), 1).to(device)

        #====================================================#
        #                  Train the Generator               #
        #====================================================#

        # random noise batches -- batch size: 32
        z = torch.randn(32, 100).to(device)
        fake_images = Gnet(z)
        g_loss = criterion(Dnet(fake_images), real_labels)

        g_optimizer.zero_grad()
        g_loss.backward()
        g_optimizer.step()

        #====================================================#
        #                Train the Discriminator             #
        #====================================================#

        d_loss_real = criterion(Dnet(imgs), real_labels)
        d_loss_fake = criterion(Dnet(fake_images.detach()), fake_labels)
        d_loss = (d_loss_real + d_loss_fake) / 2

        d_optimizer.zero_grad()
        d_loss.backward()
        d_optimizer.step()

        train_iter = train_iter  + 1

        if (i+1) % 200 == 0:
            print("Epoch [{}/{}], Step [{}/{}], d_loss: {:.4f}, g_loss: {:.4f}" \
                  .format(epoch, 200, i+1, len(train_loader), d_loss.item(), g_loss.item()))

            writer.add_scalar('g_loss', g_loss, train_iter)
            writer.add_scalar('d_loss', d_loss, train_iter)
            writer.add_image('mimic_images', vutils.make_grid(fake_images), train_iter)
            writer.add_image('real_images', vutils.make_grid(imgs), train_iter)
