import numpy as np
data = [int(x) for x in open("input.txt", "r").read().split(",")]
median = np.mode(data)
print(f"The shortest amount of fuel spend is {sum([abs(median - i) for i in data])}")

