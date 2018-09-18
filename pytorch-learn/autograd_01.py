import torch
import torchvision
from torch.autograd import Variable

# create a variable
x = Variable(torch.ones(2, 2), requires_grad = True)

print("original gridient of x: ")
print(x.grad)

y = x + 2

# z = 3 * (x+2)^2
z = y * y * 3

# out function
out = z.mean()

# calculate gradient automatically
out.backward()

print("\nAfter backward: ")
print(x.grad)
