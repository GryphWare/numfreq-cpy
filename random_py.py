import random

with open("random_num.txt", "w") as file:
    for i in range(10):
        x = random.randint(1, 10);
        file.write(str(x));
        file.write("\n");
    
with open("random_num.txt", "r") as file:
    content = file.readlines();
print(content);
