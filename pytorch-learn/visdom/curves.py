# python3 code
import torch
import visdom
import argparse
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F
from torchvision import datasets, transforms


# this time we are going show the train curve on MNIST daset
# the main code is the same as ../tinyComplete_06.py

# the steps :
# 1. load the CIFAR10 dataset
# 2. define a network
# 3. define loss function
# 4. train the network on the training set and visualize various metrics
# 5. test the trained model on the test set.

#------------------------------------------------------------ define visualizer --------------------------------------------------
DEFAULT_PORT = 8097
DEFAULT_HOSTNAME = "http://localhost"

viz = visdom.Visdom(port = DEFAULT_PORT, server = DEFAULT_HOSTNAME, env = 'train')
viz_test = visdom.Visdom(port = DEFAULT_PORT, server = DEFAULT_HOSTNAME, env = 'test')
#----------------------------------------------------------- define network structure --------------------------------------------
class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        self.conv1 = nn.Conv2d(1, 10, kernel_size=5)
        self.conv2 = nn.Conv2d(10, 20, kernel_size=5)

        # default dropout rate p = 0.5
        self.conv2_drop = nn.Dropout2d()
        self.fc1 = nn.Linear(320, 50)
        self.fc2 = nn.Linear(50, 10)

    def forward(self, x):
        x = F.relu(F.max_pool2d(self.conv1(x), 2))
        x = F.relu(F.max_pool2d(self.conv2_drop(self.conv2(x)), 2))
        x = x.view(-1, 320)
        x = F.relu(self.fc1(x))

        # note that training state should be sent to F.dropout()
        # otherwise it will not be active.
        x = F.dropout(x, training=self.training)
        x = self.fc2(x)
        return F.log_softmax(x, dim=1)

#---------------------------------------------------------- define training process ----------------------------------------------
def train(args, model, device, train_loader, optimizer, epoch, batches_num):
    # set training mode for bachNorm or dropout
    model.train()

    total_batch = batches_num

    for batch_idx, (data, target) in enumerate(train_loader):
        data, target = data.to(device), target.to(device)
        total_batch += 1

        # remember to clear grad value every iteration
        optimizer.zero_grad()
        output = model(data)
        loss = F.nll_loss(output, target)
        loss.backward()

        # update params
        optimizer.step()

        # draw loss curve of every training iteration
        viz.line(X = torch.FloatTensor([total_batch]),
                 Y = torch.FloatTensor([loss.item()]),
                 update = 'append',
                 win='train_loss',
                 opts={'title': 'train_loss',
                       'xlabel': 'iter_num',
                       'ylabel': 'loss'})

        if batch_idx % args.log_interval == 0:
            print('Train Epoch: {} [{}/{} ({:.0f}%)]\tLoss: {:.6f}'.format(
                epoch, batch_idx * len(data), len(train_loader.dataset),
                100. * batch_idx / len(train_loader), loss.item()))

    return total_batch

#----------------------------------------------------------- define test process ------------------------------------------------
def test(args, model, device, test_loader):
    # set test mode for bachNorm or dropout
    model.eval()

    test_loss = 0
    correct = 0

    # in test step, we need not to do backprob, set no_grad()
    # which is volatile() in old version
    with torch.no_grad():
        for data, target in test_loader:
            data, target = data.to(device), target.to(device)
            output = model(data)
            test_loss += F.nll_loss(output, target, reduction='sum').item() # sum up batch loss
            pred = output.max(1, keepdim=True)[1] # get the index of the max log-probability
            correct += pred.eq(target.view_as(pred)).sum().item()

    test_loss /= len(test_loader.dataset)
    print('\nTest set: Average loss: {:.4f}, Accuracy: {}/{} ({:.0f}%)\n'.format(
        test_loss, correct, len(test_loader.dataset),
        100. * correct / len(test_loader.dataset)))

    return (test_loss, correct / len(test_loader.dataset))

#---------------------------------------------------------- main process --------------------------------------------------------
def main():
    # Training settings
    parser = argparse.ArgumentParser(description='PyTorch MNIST Example')
    parser.add_argument('--batch-size', type=int, default=64, metavar='N',
                        help='input batch size for training (default: 64)')
    parser.add_argument('--test-batch-size', type=int, default=1000, metavar='N',
                        help='input batch size for testing (default: 1000)')
    parser.add_argument('--epochs', type=int, default=7, metavar='N',
                        help='number of epochs to train (default: 10)')
    parser.add_argument('--lr', type=float, default=0.01, metavar='LR',
                        help='learning rate (default: 0.01)')
    parser.add_argument('--momentum', type=float, default=0.5, metavar='M',
                        help='SGD momentum (default: 0.5)')
    parser.add_argument('--no-cuda', action='store_true', default=False,
                        help='disables CUDA training')
    parser.add_argument('--seed', type=int, default=1, metavar='S',
                        help='random seed (default: 1)')
    parser.add_argument('--log-interval', type=int, default=10, metavar='N',
                        help='how many batches to wait before logging training status')
    args = parser.parse_args()
    use_cuda = not args.no_cuda and torch.cuda.is_available()

    torch.manual_seed(args.seed)

    device = torch.device("cuda" if use_cuda else "cpu")

    kwargs = {'num_workers': 1, 'pin_memory': True} if use_cuda else {}
    train_loader = torch.utils.data.DataLoader(
        datasets.MNIST('./data', train=True, download=True,
                       transform=transforms.Compose([
                           transforms.ToTensor(),
                           transforms.Normalize((0.1307,), (0.3081,))
                       ])),
        batch_size=args.batch_size, shuffle=True, **kwargs)
    test_loader = torch.utils.data.DataLoader(
        datasets.MNIST('./data', train=False, transform=transforms.Compose([
                           transforms.ToTensor(),
                           transforms.Normalize((0.1307,), (0.3081,))
                       ])),
        batch_size=args.test_batch_size, shuffle=True, **kwargs)


    model = Net().to(device)
    optimizer = optim.SGD(model.parameters(), lr=args.lr, momentum=args.momentum)

    batches_num = 0

    for epoch in range(1, args.epochs + 1):
        batches_num = train(args, model, device, train_loader, optimizer, epoch, batches_num)
        (test_loss, test_corr) = test(args, model, device, test_loader)

        # draw loss curve and correct curve of every epoch
        viz_test.line(X = torch.FloatTensor([epoch]),
                      Y = torch.FloatTensor([test_loss]),
                      update = 'append',
                      win='test_loss',
                      opts={'title': 'test_loss',
                            'xlabel': 'epoch_num',
                            'ylabel': 'loss'})

        viz_test.line(X = torch.FloatTensor([epoch]),
                      Y = torch.FloatTensor([test_corr]),
                      update = 'append',
                      win='test_correction',
                      opts={'title': 'test_correction',
                            'xlabel': 'epoch_num',
                            'ylabel': 'corr'})


if __name__ == '__main__':
    main()
