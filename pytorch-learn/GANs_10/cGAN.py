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
img_shape = (1, 32, 32)


class Generator(nn.Module):
    def __init__(self):
        super(Generator, self).__init__()

        self.label_emb = nn.Embedding(10, 10)

        def block(in_feat, out_feat, normalize=True):
            layers = [nn.Linear(in_feat, out_feat)]
            if normalize:
                layers.append(nn.BatchNorm1d(out_feat, 0.8))
            layers.append(nn.LeakyReLU(0.2, inplace=True))
            return layers

        self.model = nn.Sequential(
            *block(100 + 10, 128, normalize=False),
            *block(128, 256),
            *block(256, 512),
            *block(512, 1024),
            nn.Linear(1024, int(np.prod(img_shape))),
            nn.Tanh()
        )

    def forward(self, noise, labels):
        # Concatenate label embedding and image to produce input
        gen_input = torch.cat((self.label_emb(labels), noise), -1)
        img = self.model(gen_input)
        img = img.view(img.size(0), *img_shape)
        return img


class Discriminator(nn.Module):
    def __init__(self):
        super(Discriminator, self).__init__()

        self.label_embedding = nn.Embedding(10, 10)

        self.model = nn.Sequential(
            nn.Linear(10 + int(np.prod(img_shape)), 512),
            nn.LeakyReLU(0.2, inplace=True),
            nn.Linear(512, 512),
            nn.Dropout(0.4),
            nn.LeakyReLU(0.2, inplace=True),
            nn.Linear(512, 512),
            nn.Dropout(0.4),
            nn.LeakyReLU(0.2, inplace=True),
            nn.Linear(512, 1),
        )

    def forward(self, img, labels):
        # Concatenate label embedding and image to produce input
        d_in = torch.cat((img.view(img.size(0), -1), self.label_embedding(labels)), -1)
        validity = self.model(d_in)
        return validity

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

# Loss functions
adversarial_loss = torch.nn.MSELoss().to(device)

# Initialize generator and discriminator
generator = Generator().to(device)
print(generator)
discriminator = Discriminator().to(device)
print(discriminator)

# Optimizers
optimizer_G = torch.optim.Adam(generator.parameters(), lr=0.0002, betas=(0.5, 0.999))
print(optimizer_G)
optimizer_D = torch.optim.Adam(discriminator.parameters(), lr=0.0002, betas=(0.5, 0.999))
print(optimizer_D)

# create summary writer
writer = SummaryWriter(log_dir='./ckpt_dir/')

train_iter = 0
for epoch in range(200):
    generator.train()
    for i, (imgs, labels) in enumerate(train_loader):
        real_labels = torch.ones(imgs.size(0), 1).type(torch.FloatTensor).to(device)
        fake_labels = torch.zeros(imgs.size(0), 1).type(torch.FloatTensor).to(device)

        imgs = imgs.type(torch.FloatTensor).to(device)
        labels = labels.type(torch.LongTensor).to(device)

        batch_size = imgs.shape[0]

        #====================================================#
        #                  Train the Generator               #
        #====================================================#

        z = torch.FloatTensor(np.random.normal(0, 1, (batch_size, 100))).to(device)
        gen_labels = torch.LongTensor(np.random.randint(0, 10, batch_size)).to(device)
        gen_imgs = generator(z, gen_labels)

        validity = discriminator(gen_imgs, gen_labels)
        g_loss = adversarial_loss(validity, real_labels)

        optimizer_G.zero_grad()
        g_loss.backward()
        optimizer_G.step()

        #====================================================#
        #                Train the Discriminator             #
        #====================================================#

        validity_real = discriminator(imgs, labels)
        d_real_loss = adversarial_loss(validity_real, real_labels)

        validity_fake = discriminator(gen_imgs.detach(), gen_labels)
        d_fake_loss = adversarial_loss(validity_fake, fake_labels)

        d_loss = (d_real_loss + d_fake_loss) / 2

        optimizer_D.zero_grad()
        d_loss.backward()
        optimizer_D.step()

        train_iter = train_iter  + 1

        if (i+1) % 200 == 0:
            print("Epoch [{}/{}], Step [{}/{}], d_loss: {:.4f}, g_loss: {:.4f}" \
                  .format(epoch, 200, i+1, len(train_loader), d_loss.item(), g_loss.item()))

            writer.add_scalar('g_loss', g_loss, train_iter)
            writer.add_scalar('d_loss', d_loss, train_iter)
            writer.add_image('mimic_images', vutils.make_grid(gen_imgs), train_iter)
            writer.add_image('real_images', vutils.make_grid(imgs), train_iter)

    generator.eval()
    with torch.no_grad():
        z = torch.FloatTensor(np.random.normal(0, 1, (10 * 10, 100))).to(device)
        labels = np.array([num for _ in range(10) for num in range(10)])
        labels = torch.LongTensor(labels).to(device)
        gen_imgs = generator(z, labels)
        writer.add_image('eval_images', vutils.make_grid(gen_imgs, nrow=10, normalize=True), epoch)
