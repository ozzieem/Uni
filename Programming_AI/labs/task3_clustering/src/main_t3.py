from client import *
from cluster import *


def main():
    choice = None
    while choice != "q":
        print_menu()
        try:
            chosen_attr = acquire_attribute()
            attribute_data_set = load_costumer_data("../files/costumer.data", chosen_attr)
            # print_list(attribute_data_set)

            choice = acquire_k_method()
            if choice == 1:
                k_value = acquire_k_value()
                clusters = k_means(attribute_data_set, k_value)
            if choice == 2:
                clusters = elbow_method(attribute_data_set)

            # print_clients_in_clusters(clusters)
            print_analysis(clusters, chosen_attr, "compact")
            choice = input("\nPress Enter to start again or q to quit...")
        except ValueError:
            print("Invalid input - enter a valid number.")
        except IndexError as e:
            print("Can't find data.", e)


def print_list(data_set):
    for val in data_set:
        print(val.client_data[0], end=", ")


def elbow_method(data_set):
    number_of_tests = 9
    sum_of_squared_errors = {}
    clusters_in_lists = [k_means(data_set, k) for k in range(1, number_of_tests + 1)]

    # calculate error and mean for each cluster
    for k, clusters in enumerate(clusters_in_lists):
        sum_of_squared_errors[k] = 0
        for cluster in clusters:
            mean = sum([sum(client.client_data) for client in cluster.clients]) / len(cluster.clients)
            sum_of_squared_errors[k] += sum([(client.client_data[0] - mean) ** 2 for client in cluster.clients])

    # convert the gains to percentage values
    print("Cluster\t|\tPercentage of variance:")
    gains = []
    for key, err in sum_of_squared_errors.items():
        gain = (1 - err / sum_of_squared_errors[0]) * 100
        gains.append(gain)
        print("\t", key + 1, "\t\t", gain)

    # find the elbow through first and second differences of gains
    f_diff = [abs(j - i) for i, j in zip(gains, gains[2:])]
    # print("First diff:", f_diff)
    s_diff = [j - i for i, j in zip(f_diff, f_diff[2:])]
    # print("Second diff:", s_diff)

    # get the index with the biggest change
    val, idx = min((val, idx) for (idx, val) in enumerate(s_diff))

    print("Elbow curve detected. Optimal K-value:", idx + 3)
    return clusters_in_lists[idx + 2]


def print_menu():
    print("\nAttributes:\n 1. Fresh\n 2. Milk\n 3. Grocery\n 4. Frozen\n 5. Detergents paper\n 6. Delicatessen ")


def acquire_k_method():
    while True:
        try:
            choice = int(input("K-means\n 1. Manual K-value\n 2. Elbow-method\n"))
            if choice < 1 or choice > 2:
                raise IndexError
            return choice
        except IndexError:
            print("Invalid input - Choose an option")


def acquire_attribute():
    chosen_attr = int(input("Enter your chosen attribute:"))
    if chosen_attr < 1 or chosen_attr > 6:
        raise IndexError("Invalid input - chosen attribute not listed.")
    return chosen_attr


def acquire_k_value():
    while True:
        try:
            val = int(input("K-value:"))
            return val
        except ValueError:
            print("Enter a valid K-value")


def print_clients_in_clusters(clusters):
    idx = 0
    for i, c in enumerate(clusters):
        for j, p in enumerate(c.clients):
            idx += 1
            print(idx, "\tCLUSTER " + str(i + 1) + ":\t\tCLIENT: " + str(p))


def print_analysis(clusters, attr, mode="full"):
    attributes = {1: "Fresh", 2: "Milk", 3: "Grocery", 4: "Frozen", 5: "Detergents paper", 6: "Delicatessen"}
    print("\n-----------------------------ANALYSIS-----------------------------")
    print(f"Annual spending for attribute <{attributes[attr]}> - {len(clusters)} groups identified:")
    cluster_groups = [[] for __ in clusters]
    channels = [[] for __ in clusters]
    regions = [[] for __ in clusters]
    idx = 0
    for i, c in enumerate(clusters):
        for p in c.clients:
            cluster_groups[i].append(p.client_data[0])
            channels[i].append(p.channel)
            regions[i].append(p.region)
            idx += 1
        max_val = max(cluster_groups[i])
        min_val = min(cluster_groups[i])
        cluster_centroid = clusters[i].centroid.client_data[0]
        above_centroid = max_val - cluster_centroid
        under_centroid = cluster_centroid - min_val
        cluster_size = len(clusters[i].clients)
        cluster_size_percent = int((cluster_size / 440) * 100)
        cluster_channel_size_percent = lambda x: int(channels[i].count(x) / len(channels[i]) * 100)
        cluster_region_size_percent = lambda x: int(regions[i].count(x) / len(regions[i]) * 100)
        if mode == "full":
            print(f"CLUSTER {i + 1} (Centroid:{cluster_centroid}):\n"
                  f"\tSize - {cluster_size} ({cluster_size_percent}%)\n"
                  f"\tSpending - [{min_val} - {max_val}]\n"
                  f"\tChannel:\n"
                  f"\t\tHotels/Restaurants/Cafe - {channels[i].count(1)} ({cluster_channel_size_percent(1)}%)\n"
                  f"\t\tRetail                  - {channels[i].count(2)} ({cluster_channel_size_percent(2)}%)\n"
                  f"\tRegion:\n"
                  f"\t\tLisbon - {regions[i].count(1)} ({cluster_region_size_percent(1)}%)\n"
                  f"\t\tOporto - {regions[i].count(2)} ({cluster_region_size_percent(2)}%)\n"
                  f"\t\tOther  - {regions[i].count(3)} ({cluster_region_size_percent(3)}%)\n"
                  )
        elif mode == "compact":
            print(
                f"CLUSTER {i + 1} (Size: {cluster_size} ({cluster_size_percent}%)):\n"
                f"\tChannel  - [{channels[i].count(1)}, {channels[i].count(2)}]\t&"
                f"\tRegion - [{regions[i].count(1)}, {regions[i].count(2)}, {regions[i].count(3)}]\n"
                f"\tSpending - [{min_val} - ({cluster_centroid}) - {max_val}]\n"
                f"\t\t\t\t\t({under_centroid} | {above_centroid})"
                f"\n\t\t\t\t\t\t({above_centroid - under_centroid})\n"

            )
        elif mode == "full_text":
            print(
                f"Group {i+1} has {cluster_size} customers ({cluster_size_percent}% of total customers) spending \nbetween {min_val} to {max_val}. "
                f"{channels[i].count(1)} ({cluster_channel_size_percent(1)}%) of the customers spends money \non Hotels/Restaurants and Cafes while "
                f"{channels[i].count(2)} ({cluster_channel_size_percent(2)}%) spends on Retail.\n"
                f"{regions[i].count(1)} ({cluster_region_size_percent(1)}%) of the customers lives in Lisbon, "
                f"{regions[i].count(2)} ({cluster_region_size_percent(2)}%) lives in Oporto\nwhile "
                f"{regions[i].count(3)} ({cluster_region_size_percent(3)}%) lives in other regions.\n"
            )
        elif mode == "compact_text":
            print(f"Group {i+1} has {cluster_size} customers ({cluster_size_percent}% of total customers)\n"
                  f"Spends between {min_val} to {max_val}\n"
                  f"{channels[i].count(1)}\t({cluster_channel_size_percent(1)}%)\tspends money on Hotels/Restaurants and Cafes\n"
                  f"{channels[i].count(2)}\t({cluster_channel_size_percent(2)}%)\tspends money on Retail\n"
                  f"{regions[i].count(1)}\t({cluster_region_size_percent(1)}%)\tlives in Lisbon\n"
                  f"{regions[i].count(2)}\t({cluster_region_size_percent(2)}%)\tlives in Oporto\n"
                  f"{regions[i].count(3)}\t({cluster_region_size_percent(3)}%)\tlives in other regions\n"
                  )
    print("------------------------------------------------------------------")


main()
