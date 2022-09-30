

class DisjointSet:

    def __init__(self, n) -> None:
        self.roots = [i for i in range(n)]
        self.rank = [0] * n

    def find(self, x) -> int:
        if self.roots[x] == x:
            return x
        self.roots[x] = self.find(self.roots[x])
        return self.roots[x]

    def union(self, x, y) -> None:
        rootX = self.find(x)
        rootY = self.find(y)
        if rootX != rootY:
            if self.rank[rootX] > self.rank[rootY]:
                self.roots[rootY] = rootX
            elif self.rank[rootX] < self.rank[rootX]:
                self.roots[rootX] = rootY
            else:
                self.roots[rootY] = rootX
                self.rank[rootX] += 1


            