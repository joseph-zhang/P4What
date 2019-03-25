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
        return img,label

    def __len__(self):
        return len(self.imgs)

cust_transform = transforms.Compose([transforms.ToTensor(),
                                     transforms.Normalize(mean=(0.5, 0.5, 0.5),
                                                          std=(0.5, 0.5, 0.5))])

img_shape = (1, 28, 28)

train_data = MyDataset(image_dir = root+'train.txt', transform=cust_transform)
train_loader = DataLoader(dataset=train_data, batch_size=32, shuffle=True)


# ------------------------------------------------------------ Network Definition -------------------------------------------------------------

# define Discriminator
class Discriminator(nn.Module):
    def __init__(self):
        super(Discriminator, self).__init__()

        self.model = nn.Sequential(
            nn.Linear(int(np.prod(img_shape)), 512),
            nn.LeakyReLU(0.2, inplace=True),
            nn.Linear(512, 256),
            nn.LeakyReLU(0.2, inplace=True),
            nn.Linear(256, 1),
            nn.Sigmoid()
        )

    def forward(self, img):
        img_flat = img.view(img.size(0), -1)
        validity = self.model(img_flat)

        return validity

# define Generator
class Generator(nn.Module):
    def __init__(self):
        super(Generator, self).__init__()

        def block(in_feat, out_feat, normalize=True):
            layers = [nn.Linear(in_feat, out_feat)]
            if normalize:
                layers.append(nn.BatchNorm1d(out_feat, 0.8))
            layers.append(nn.LeakyReLU(0.2, inplace=True))
            return layers

        self.model = nn.Sequential(
            *block(100, 128, normalize=False),
            *block(128, 256),
            *block(256, 512),
            *block(512, 1024),
            nn.Linear(1024, int(np.prod(img_shape))),
            nn.Tanh()
        )

    def forward(self, z):
        img = self.model(z)
        img = img.view(img.size(0), *img_shape)
        return img

# ----------------------------------------------------------------- Training steps --------------------------------------------------------------

device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")

# create summary writer
writer = SummaryWriter(log_dir='./ckpt_dir/')

Dnet = Discriminator().to(device)
Gnet = Generator().to(device)
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
