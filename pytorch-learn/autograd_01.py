import torch

# =================================================================

# (create a variable/tensor)
# Actually, Variable has been diprecated in 0.4
# it has been binded to tensor naturally
x = torch.ones(2, 2, requires_grad = True)

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

# =================================================================

x = torch.tensor(1., requires_grad=False)
w = torch.tensor(2., requires_grad=True)
b = torch.tensor(3., requires_grad=True)

y = w * x + b

# Compute gradients.
y.backward()

# Print out the gradients.
print(x.grad)  # None
print(w.grad)  # 1.
print(b.grad)  # 1.
