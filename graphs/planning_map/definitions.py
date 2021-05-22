from __future__ import print_function

# an example implementation of a FIFO in python
class SimpleQueue:
    def __init__(self):
        self.items = []

    def isEmpty(self):
        return self.items == []


    def empty(self):
        return self.items == []

    def put(self, item):
        self.items.insert(0,item)

    def get(self):
        return self.items.pop()

    def qsize(self):
        return len(self.items)

class BColors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'

    def disable(self):
        self.HEADER = ''
        self.OKBLUE = ''
        self.OKGREEN = ''
        self.WARNING = ''
        self.FAIL = ''
        self.ENDC = ''



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

    def __eq__(self,other):
        """Overrides the default implementation"""
        if isinstance(other, Location):
            return (self.x == other.x and self.y == other.y)
        return False


    def __ne__(self,other):
        """Overrides the default implementation (unnecessary in Python 3)"""
        return not self.__eq__(other)

    def get(self):
        return [self.x,self.y]
    def set(self,input_loc):
        self.x = input_loc[0]
        self.y = input_loc[1]


class Tile:
    def __init__(self,loc,blocked_state):
        if isinstance(loc,Location):
            self.location = Location(loc.x, loc.y)
        else:
            self.location = Location(0,0)
            raise TypeError('input location should be a Location class object')

        self.blocked = 1
        if not blocked_state:
            self.blocked = 0
        self.weight = 1

    def isBlocked(self):
        if self.blocked:
            return True
        return False


class WorldMap:
    def __init__(self,xy_size):
        if xy_size:
            self.grid_size = xy_size
        else:
            self.grid_size = 1

        self.map = []
        self.initWorldMap()

    def initWorldMap(self):
        for i in xrange(self.grid_size):
            row = []
            for j in xrange(self.grid_size):
                col_tile = Tile(Location(i,j),False)
                # print( i , j)
                row.append(col_tile)
            self.map.append(row)



    def size():
        return self.grid_size

    def getLocation(self):
        return 0

    def getNonBlockedNeighbors(self,loc):
        if isinstance(loc,list):
            location = Location(loc[0],loc[1])
        elif isinstance(loc,Location):
            location = loc
        else:
            raise TypeError('input location should be either a Location class object or a list')

        directions = ['r','d','l','u']
        neighbors = []
        # find neighbors of the current location
        for dir_i in directions:
            if dir_i == 'r':
                next_location = Location(location.x+1,location.y)

            elif dir_i == 'd':
                next_location = Location(location.x,location.y-1)

            elif dir_i == 'l':
                next_location = Location(location.x-1,location.y)

            elif dir_i == 'u':
                next_location = Location(location.x,location.y+1)

            # print(next_location.x,next_location.y)

            # check if the next location is not outside of the map borders
            if (next_location.x >= 0) and (next_location.y >= 0) and \
                (next_location.x < self.grid_size) and \
                (next_location.y < self.grid_size):

                if not self.map[next_location.x][next_location.y].isBlocked():
                    neighbors.append(next_location)

            # end of for dir_i

        return neighbors

    def show(self):
        for row_tiles in self.map:
            for col_tiles in row_tiles:
                print(col_tiles.blocked,end=' ')
            print('')
