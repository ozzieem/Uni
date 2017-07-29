import math
from random import randrange, uniform

class Wine:
    def __init__(self, cultivar, alcohol, malic_acid, ash, alcalinity_of_ash, magnesium, total_phenols, flavanoids, nonflavanoid_phenols, proanthocyanins, color_intensity, hue, diluted_wines, proline):
        self.cultivar = cultivar
        self.alcohol = alcohol
        self.malic_acid = malic_acid
        self.ash = ash
        self.alcalinity_of_ash = alcalinity_of_ash
        self.magnesium = magnesium
        self.total_phenols = total_phenols
        self.flavanoids = flavanoids
        self.nonflavanoid_phenols = nonflavanoid_phenols
        self.proanthocyanins = proanthocyanins
        self.color_intensity = color_intensity
        self.hue = hue
        self.diluted_wines = diluted_wines
        self.proline = proline

        self.value = (alcohol + malic_acid + ash + alcalinity_of_ash + magnesium + total_phenols + flavanoids + nonflavanoid_phenols + proanthocyanins + color_intensity + hue + diluted_wines + proline)
    
    def __str__(self):
        return "(" + str(self.alcohol) + ", " + str(self.value) + ")"


class Cluster:
    def __init__(self, centroid):
        self.centroid_pos = centroid
        self.winecluster = []

    def update_centroid(self, centroid):
        self.centroid_pos = centroid

    def add_wine_to_cluster(self, wine):
        self.winecluster.append(wine)

    def recalc_centroid(self):
        total_pos = 0
        num_of_wines = len(self.winecluster)
        if(num_of_wines > 0):
            for wine in self.winecluster:
                total_pos += wine.value
            self.update_centroid(total_pos / num_of_wines)

    def clear_winecluster(self):
        self.winecluster = []

    def print_cluster(self):
        for wine in self.winecluster:
            print(wine.alcohol)

    def print_cluster_cultivar(self):
        for wine in self.winecluster:
            print(wine.cultivar)



def create_wine_list():
    obj = open("wine.data")
    while(1):
        line = obj.readline()
        if len(line) <= 3:
            break
        nums = line.split(',', 14)
    
        cult = eval(nums[0])
        alc = eval(nums[1])
        malic = eval(nums[2])
        ash = eval(nums[3])
        alcal = eval(nums[4])
        magn = eval(nums[5])
        totp = eval(nums[6])
        flava = eval(nums[7])
        nonflava = eval(nums[8])
        proa = eval(nums[9])
        color = eval(nums[10])
        hue = eval(nums[11])
        diluted = eval(nums[12])
        proline = eval(nums[13])

        win = Wine(cult, alc, malic, ash, alcal, magn, totp, flava, nonflava, proa, color, hue, diluted, proline)
        wineslist.append(win)
    obj.close()

wineslist = []
create_wine_list()

def calc_dist_to_centroids(wine, clusters):
    dist = 10000
    for clust in clusters:
        dist_temp = math.sqrt((wine.value - clusters.get(clust).centroid_pos) * (wine.value - clusters.get(clust).centroid_pos))
        if dist_temp < dist:
            dist = dist_temp
            actual_cluster = clust
    (clusters.get(actual_cluster)).add_wine_to_cluster(wine)


def create_centroids(num_of_centroids, wineslist):
    centroids = []
    max = 0
    min = 10000
    for wine in wineslist:
        if wine.value < min:
            min = wine.value
        if wine.value > max:
            max = wine.value
    for cent in range (0, num_of_centroids):
        centroid = uniform(min, max)
        centroids.append(centroid)
    return centroids


def equal_centroid_pos(old_centroids, new_centroids):
    i = 1
    for old in old_centroids:
        if old != new_centroids.get(i).centroid_pos:
            return 0
        i += 1
    return 1

def kmeans(wineslist, num_of_centroids, max_iterations):
    iterations = 0
    clusters = {}
    centroids = create_centroids(num_of_centroids, wineslist)
    i = 1
    for cent in centroids:
        clusters[i] = Cluster(cent)
        i += 1 
    for wine in wineslist:
        calc_dist_to_centroids(wine, clusters)
    
    while(iterations < max_iterations):
        iterations += 1
        old_centroids = []
        for clust in clusters:
            old_centroids.append(clusters.get(clust).centroid_pos)
            clusters.get(clust).recalc_centroid()
        equal = equal_centroid_pos(old_centroids, clusters)
        if equal == 1:
            break
        for clust in clusters:
            clusters.get(clust).clear_winecluster()
        for wine in wineslist:
            calc_dist_to_centroids(wine, clusters)
	
    # print info
    for i, c in enumerate(clusters):
        for w in clusters[c].winecluster:
            print("Cluster: ", i, "\t Wine :", w)
    print("Iterations: ", iterations)


kmeans(wineslist[:10], 3, 20)