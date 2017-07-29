import math
import random

from client import Client


# TODO: maybe make this into a class
def k_means(customers, k_value):
    # pick out k initial centroids
    initial_centroids = random.sample(customers, k_value)

    # create clusters with centroids
    clusters = [Cluster([c]) for c in initial_centroids]
    print("Initial centroids: ", [c for c in initial_centroids])

    clients_in_cluster = {}  # clients that will be grouped to a cluster
    n_iterations = 0

    while True:
        n_iterations += 1

        # reset current clients in cluster
        for c in clusters:
            clients_in_cluster[c] = []
        assign_clients_to_cluster(clients_in_cluster, clusters, customers)

        converged = update_clusters(clients_in_cluster)

        if converged:
            # print(f"Centroids in iteration {n_iterations - 1} and {n_iterations} are identical - Converging complete. ")
            print(f"Total iterations: {n_iterations}\n")
            return clusters


def update_clusters(clients_in_cluster):
    old_centroids = []
    new_centroids = []
    # update all clusters
    for cluster, clients in clients_in_cluster.items():
        old_centroids.append(cluster.centroid)
        new_centroid = cluster.update(clients_in_cluster[cluster])
        new_centroids.append(new_centroid)

    # print(f"{iteration}.\t Updated centroids: {new_centroids}")

    # check if the centroid have stopped moving (have converged)
    return is_same_centroid(old_centroids, new_centroids)


def assign_clients_to_cluster(clients_in_cluster, clusters, customers):
    # assign each client to a cluster
    for c in customers:
        min_distance = math.inf

        for cluster in clusters:
            # get distance for a cluster
            distance = minkowski_distance(c.client_data, cluster.centroid.client_data)

            # check if the acquired distance is the smallest and add it to the cluster
            if distance < min_distance:
                min_distance = distance
                add_to_cluster = cluster
        clients_in_cluster[add_to_cluster].append(c)


def is_same_centroid(old_centroids, new_centroids):
    for i, c in enumerate(old_centroids):
        if not c.equal(new_centroids[i]):
            return False
    return True


LAMBDA = 3


def minkowski_distance(a, b):
    dist = 0

    for idx, v1 in enumerate(a):
        dist += (abs(v1 - b[idx])) ** LAMBDA

    dist **= 1 / LAMBDA
    return dist


class Cluster:
    def __init__(self, clients):
        self.clients = clients
        self.centroid = clients[0]

    def update(self, clients):
        self.clients = clients
        self.centroid = self.calculate_centroid()
        return self.centroid

    def calculate_centroid(self):
        lists = [c.client_data for c in self.clients]
        # produce a list with average value of all clients data
        centroid_mean = [int(sum(x) / self.size_clients()) for x in zip(*lists)]
        return Client(centroid_mean)

    # def __repr__(self):
    #     return str(f"Cluster: {self.clients}")

    def __repr__(self):
        return f"ClusterCent: {self.centroid.client_data}"

    def size_clients(self):
        return len(self.clients)
