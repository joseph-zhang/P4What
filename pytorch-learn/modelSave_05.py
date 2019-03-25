# python3 code
import torch
import torchvision
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim

# Define Network AlexNet
class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        self.conv1 = nn.Conv2d(3, 6, 5)
        self.pool = nn.MaxPool2d(2, 2)
        self.conv2 = nn.Conv2d(6, 16, 5)
        self.fc1 = nn.Linear(16 * 5 * 5, 120)
        self.fc2 = nn.Linear(120, 84)
        self.fc3 = nn.Linear(84, 10)

    def forward(self, x):
        x = self.pool(F.relu(self.conv1(x)))
        x = self.pool(F.relu(self.conv2(x)))
        x = x.view(-1, 16 * 5 * 5)
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        x = self.fc3(x)
        return x

# Initialize model
model = Net()

# Initialize optimizer
optimizer = optim.SGD(model.parameters(), lr=0.001, momentum=0.9)

# There are three key function related to model saving:
# 1. torch.save --> use pickle to do serialization;
# 2. torch.load --> unpicking the serialized file and load them in memory;
# 3. torch.nn.Module.load_state_dict --> check stateDict.py

# ------------------------------------------- save/load stateDict (learning params) ------------------------------
# which is often used to save well trained model parameters.

# save
torch.save(model.state_dict(), './statedict.pth')

# load
new_model = Net()
model.load_state_dict(torch.load('./statedict.pth'))
# remember invoke this to set dropout and batch normalization layers to evaluation mode before running inference.
model.eval()

# ------------------------------------------- save/load entire model directly -------------------------------------
# save entire model parameters, also save graph structure info.

# save
torch.save(model, './entire_model.pth')

# load
new_model = torch.load('./entire_model.pth')
model.eval()

# ------------------------------------------- save/load checkpoint -----------------------------------------------
# checkpoint is more often to be saved, for it contains not only model sate_dict but also training params in optimizer.
# If you want to restore training process, checkpoint file is always needed.
# Note that is often included in iterative loop.
torch.save({
    'epoch': epoch,
    'model_state_dict': model.state_dict(),
    'optimizer_state_dict': optimizer.state_dict(),
    'loss': loss}, './checkpoint.pth.tar')

# load checkpoint
model = TheModelClass(*args, **kwargs)
optimizer = TheOptimizerClass(*args, **kwargs)

checkpoint = torch.load('./checkpoint.pth.tar')
model.load_state_dict(checkpoint['model_state_dict'])
optimizer.load_state_dict(checkpoint['optimizer_state_dict'])
epoch = checkpoint['epoch']
loss = checkpoint['loss']

# invoke eval() to set dropout and batch normalization layers to evaluation mode before running inference.
model.eval()
# - or -
# invoke train() to set these layers to training mode.
model.train()
