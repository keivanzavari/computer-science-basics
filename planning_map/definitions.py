# an example implementation of a FIFO in python
class SimpleQueue:
    def __init__(self):
        self.items = []

    def isEmpty(self):
        return self.items == []

    def enqueue(self, item):
        self.items.insert(0,item)

    def dequeue(self):
        return self.items.pop()

    def size(self):
        return len(self.items)


class Map:
    def __init__(self,size):
        if size:
            self.grid_size = size
        else:
            self.grid_size = 1


    def size():
        return self.grid_size

    def getNextLocation(self,location, direction):

    def set(self,input_loc):
        self.x = input_loc[0]
        self.y = input_loc[1]

class Location:
    def __init__(self,x_val=None,y_val=None):
        if x_val:
            self.x = x_val
        else:
            self.x = 0

        if y_val:
            self.y = y_val
        else:
            self.y = 0
    def get():
        return [self.x,self.y]
    def set(self,input_loc):
        self.x = input_loc[0]
        self.y = input_loc[1]
