

struct DisjointSet {
    roots: Vec<usize>,
    rank: Vec<usize>
}

impl DisjointSet {
    
    fn new(n: usize) -> Self {
        return DisjointSet { roots: (0..n).collect(), rank: vec![0;n]};
    }

    fn find(&mut self, x: usize) -> usize {
        if x == self.roots[x] {
            return x;
        }
        self.roots[x] = self.find(self.roots[x]);
        return self.roots[x];
    }

    fn union(&mut self, x: usize, y: usize) {
        let rootX: usize = self.find(x);
        let rootY: usize = self.find(y);
        if rootX != rootY {
            if self.rank[rootX] > self.rank[rootY] {
                self.roots[rootY] = rootX;
            } else if self.rank[rootX] < self.rank[rootX] {
                self.roots[rootX] = rootY;
            } else {
                self.roots[rootY] = rootX;
                self.rank[rootX] += 1;
            }
        }
    }    
}
