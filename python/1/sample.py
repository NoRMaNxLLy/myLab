paths = {
    (1, 7): {
        "i": 0,
        "paths": [[1, 2, 7], [1, 2, 5, 7], [1, 3, 4, 7]]
    }
}

i = paths[1, 7]["i"]
n = len(paths[1, 7]["paths"])
print(paths[1, 7]["paths"][i % n])

i += 1
print(paths[1, 7]["paths"][i % n])

i += 1
print(paths[1, 7]["paths"][i % n])

i += 1
print(paths[1, 7]["paths"][i % n])

i += 1
print(paths[1, 7]["paths"][i % n])

i += 1
print(paths[1, 7]["paths"][i % n])

i += 1
print(paths[1, 7]["paths"][i % n])

i += 1
print(paths[1, 7]["paths"][i % n])
