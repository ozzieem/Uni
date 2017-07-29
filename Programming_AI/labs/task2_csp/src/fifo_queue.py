class FIFOQueue:
    size = 0
    items = []

    def __init__(self, variables):
        self.items = variables
        self.size = len(self.items)
        self.set_size()

    def get(self):
        item = self.items[0]
        del self.items[0]
        self.set_size()
        return item

    def put(self, obj):
        self.items.append(obj)

    def set_size(self):
        self.size = len(self.items)

    def empty(self):
        if self.size <= 0:
            return True
        else:
            return False

    def __str__(self):
        return str(self.items)

