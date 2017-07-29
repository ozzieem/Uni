def next_configuration(y):
    """Take a configuration of heaps and remove one card from each
    heap to create a new heap.
    """
    new_y = [x - 1 for x in y if x > 1]
    new_y.append(len(y))
    new_y.sort(reverse=True)
    return new_y

config = [4,4,2]
print(config)
for i in range(25):
    new_config = next_configuration(config)
    print("New: " + str(new_config))
    if new_config == config:
        print("Same as previous, aborting")
        break
    config = new_config
