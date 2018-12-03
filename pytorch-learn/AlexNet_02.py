import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim

# torch.nn is the key to define a network
# torch.nn.functional define a lot of useful functions, such as relu, max_pool2d ..

# -------------------------------------------------------- step 1: define Network -------------------------------------------------
# define a Net subclass
class Net(nn.Module):
    def __init__(self):
        # use the __init__ funcction of its father class
        super(Net, self).__init__()

        # define inner variables
        # torch.nn.Conv2d(in_channels, out_channels, kernel_size,
        #                 stride=1, padding=0, dilation=1, groups=1, bias=True)
        self.conv1 = nn.Conv2d(1, 6, 5)
        self.conv2 = nn.Conv2d(6, 16, 5)

        # fc layers
        self.fc1 = nn.Linear(16 * 5 * 5, 120)
        self.fc2 = nn.Linear(120, 84)
        self.fc3 = nn.Linear(84, 10)


    # once the forward function is defined,
    # the backward method will be implemented automatically
    def forward(self, x):
        x = F.max_pool2d(F.relu(self.conv1(x)), (2, 2))
        # 2 is enough
        x = F.max_pool2d(F.relu(self.conv2(x)), 2)
        x = x.view(-1, self.num_flat_features(x))

        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        x = self.fc3(x)

        return x

    def num_flat_features(self, x):
        size = x.size()[1:]
        num_features = 1
        for s in size:
            num_features *= s
        return num_features


# --------------------------------------------------------- step 2: define loss function --------------------------------------------
net = Net()
params = list(net.parameters())
print(len(params))

# suppose we have an input image
# instance_num, channels, size_x, size_y
input = torch.randn(1, 1, 32, 32)
output = net(input)

# suppose we have the corresponding ground truth
# note that the gt type is LongTensor :: int64
gt = torch.arange(1, 11, out = torch.FloatTensor())
gt = gt.view(1,-1)

criterion = nn.MSELoss()

# define loss function as MSE
loss = criterion(output, gt)
print(loss)

#print(loss.grad_fn)
#print(loss.grad_fn.next_functions[0][0])
#print(loss.grad_fn.next_functions[0][0].next_functions[0][0]) 

# remember to clear the variable value before calculate the gradient
net.zero_grad()

print('conv1.bias.grad before backward')
print(net.conv1.bias.grad)

loss.backward()

# every time the result of grad is different from each other
print('conv1.bias.grad after backward')
print(net.conv1.bias.grad)

# --------------------------------------------------------- step 3: Update the weights ------------------------------------------------
# define an optimizer
optimizer = optim.SGD(net.parameters(), lr = 0.01)

# training
optimizer.zero_grad()

# does the update
optimizer.step()
