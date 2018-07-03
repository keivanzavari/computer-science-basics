import Queue as q
from definitions import Location
a = q.Queue()

start = Location(0,0)
frontier = q.Queue()
frontier.put(start)
visited = {}
visited[start] = True

while not frontier.empty():
    current = frontier.get()
    directions = ['r','d','l','u']

    # find neighbors of the current location
    for dir_i in directions:
        if dir_i == 'r':
            
        elif dir_i == 'd':
        elif dir_i == 'l':
        elif dir_i == 'u':
        graph.neighbors(current)
    for next in graph.neighbors(current):
        if next not in visited:
            frontier.put(next)
            visited[next] = True

