
N = 4
INF = 999


def display_routing_tables(dist, next_hop):
    for i in range(N):
        print(f"\nRouting Table for Router {i}:")
        print("Destination\tCost\tNext Hop")

        for j in range(N):
            cost_str = "INF" if dist[i][j] == INF else str(dist[i][j])
            hop_str = "-" if next_hop[i][j] == -1 else str(next_hop[i][j])

            print(f"{j}\t\t{cost_str}\t{hop_str}")


def print_path(src, dest, next_hop):
    temp = src
    print(temp, end="")

    while temp != dest:
        temp = next_hop[temp][dest]
        print(f" -> {temp}", end="")

    print()


cost = [[0] * N for _ in range(N)]
dist = [[0] * N for _ in range(N)]
next_hop = [[-1] * N for _ in range(N)]

print("Enter the cost matrix (4x4) [Use 999 for INF]:")

for i in range(N):
    for j in range(N):
        cost[i][j] = int(input(f"Enter the cost between {i} & {j}: "))

for i in range(N):
    for j in range(N):
        dist[i][j] = cost[i][j]

        if i == j:
            next_hop[i][j] = i
        elif cost[i][j] != INF:
            next_hop[i][j] = j
        else:
            next_hop[i][j] = -1

print("\nINITIAL ROUTING TABLE")
display_routing_tables(dist, next_hop)

updated = True

while updated:
    updated = False

    for i in range(N):
        for j in range(N):
            for k in range(N):
                if (
                    dist[i][k] != INF
                    and dist[k][j] != INF
                    and dist[i][j] > dist[i][k] + dist[k][j]
                ):
                    dist[i][j] = dist[i][k] + dist[k][j]
                    next_hop[i][j] = next_hop[i][k]
                    updated = True

print("\nFINAL ROUTING TABLE")
display_routing_tables(dist, next_hop)

print("\nShortest Path Finder")
src = int(input(f"Enter Source Node (0 to {N - 1}): "))
dest = int(input(f"Enter Destination Node (0 to {N - 1}): "))

if dist[src][dest] == INF:
    print(f"No path exists between node {src} and node {dest}")
else:
    print("Minimum Cost:", dist[src][dest])
    print("Shortest Path: ", end="")
    print_path(src, dest, next_hop)
