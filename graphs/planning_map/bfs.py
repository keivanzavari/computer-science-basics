import Queue as q
from definitions import Location, Tile, WorldMap, BColors, SimpleQueue


world_map = WorldMap(4)
world_map.show()

start = Location(0,0)
frontier = SimpleQueue()
frontier.put(start)
visited = {}
visited[start.x,start.y] = True

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

        print BColors.OKGREEN+'frontier size: ', frontier.qsize(), BColors.ENDC
        print 'current location: ', current_location.x, current_location.y
        print 'neighbors of size: ', len(neighbors)
        counter += 1

    if len(neighbors) == 0:
        print BColors.FAIL+'neighbors list empty, current_location: ', \
        current_location.x, current_location.y , BColors.ENDC

    # neighbors is a list of max four Location objects
    for next in neighbors:
        if counter < counter_max:
            print 'visited length: ', len(visited)
            print 'visited contains'
            for loc_i in visited.keys():
                print loc_i[0] , loc_i[1]

        if (next.x,next.y) not in visited:
            if counter < counter_max:
                print  BColors.OKBLUE + 'adding ', next.x, next.y , BColors.ENDC

            frontier.put(next)
            visited[next.x,next.y] = True

    # if iteration == 100:
    #     break




# ------------------------------------------
# print frontier
# ------------------------------------------



print 'frontier size: ', frontier.qsize()
print BColors.HEADER+'============================================='+\
        BColors.ENDC

if False:
    iteration = 0
    while not frontier.empty():
        iteration += 1

        current_location = frontier.get()

        print BColors.HEADER+'----------------------------------------------'+\
        BColors.ENDC
        print BColors.OKGREEN+'frontier size: ', frontier.qsize(), BColors.ENDC
        print BColors.OKBLUE+'current location: ', current_location.x, current_location.y, BColors.ENDC

        if iteration == 10:
            break