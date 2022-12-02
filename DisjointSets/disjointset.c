#include <stdlib.h>

struct DisJointSet {
    int* roots;
    int* ranks;
    (int) (*find)(struct DisJointSet* self, int x);
    (void) (*union)(struct DisJointSet* self);
};

struct DisJointSet DisJointSet(int n) {
    struct DisJointSet* disjointset = (struct DisJointSet*)malloc(sizeof(struct DisJointSet));
    int* roots = (int*)malloc(sizeof(int) * n);
    int* ranks = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        roots[i] = i;
        ranks[i] = 0;
    }
    disjointset -> roots = roots;
    disjointset -> ranks = ranks;
    return disjointset;
}

int find(struct DisJointSet* self, int x) {
    if (self -> roots[x] == x) {
        return x;
    }
    self -> roots[x] = find(self, self -> roots[x]);
    return self -> roots[x];
}

void union(struct DisJointSet* self, int x, int y) {
    int rootX = self -> find(self, x);
    int rootY = self -> find(self, y);
    if (rootX != rootY) {
        if (self -> ranks[rootX] > self -> ranks[rootY]) {
            self -> roots[rootY] = rootX;
        } else if (self -> ranks[rootX] < self -> ranks[rootY]) {
            self -> roots[rootX] = rootY;
        } else {
            self -> roots[rootY] = rootX;
            self -> ranks[rootX] += 1;
        }
    }
}

