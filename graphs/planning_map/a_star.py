import Queue as q
from definitions import Location, Tile, WorldMap, BColors, SimpleQueue

world_map = WorldMap(4)
world_map.show()

start = Location(0, 0)
frontier = SimpleQueue()
frontier.put(start)
came_from = {}
came_from[start.x, start.y] = None

counter = 0
counter_max = 1
iteration = 0
while not frontier.empty():
    iteration += 1
    current_location = frontier.get()
    neighbors = world_map.getNonBlockedNeighbors(current_location)
    if counter < counter_max:
        print BColors.HEADER+'----------------------------------------------'+\
        BColors.ENDC

        print BColors.OKGREEN + 'frontier size: ', frontier.qsize(), BColors.ENDC
        print 'current location: ', current_location.x, current_location.y
        print 'neighbors of size: ', len(neighbors)
        counter += 1

    if len(neighbors) == 0:
        print BColors.FAIL+'neighbors list empty, current_location: ', \
        current_location.x, current_location.y , BColors.ENDC

    # neighbors is a list of max four Location objects
    for next in neighbors:
        if counter < counter_max:
            print 'came_from length: ', len(came_from)
            print 'came_from contains'
            for loc_i in came_from.keys():
                print loc_i[0], loc_i[1]

        if (next.x, next.y) not in came_from:
            if counter < counter_max:
                print BColors.OKBLUE + 'adding ', next.x, next.y, BColors.ENDC

            frontier.put(next)
            came_from[next.x, next.y] = current_location

    if current_location == goal:
        break

# ------------------------------------------
# reconstruct path
# ------------------------------------------

goal = Location(3, 3)
current = goal
path = []
while current != start:
    path.append(current.get())
    current = came_from[current.x, current.y]
path.append(start.get())  # optional
path.reverse()  # optional
