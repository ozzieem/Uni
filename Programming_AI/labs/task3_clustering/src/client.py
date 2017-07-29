# Channel,Region,Fresh,Milk,Grocery,Frozen,Detergents_Paper,Delicassen
class Client:
    client_data = []

    def __init__(self, costumer_data):
        self.client_data = costumer_data
        self.channel = 0
        self.region = 0

    def __repr__(self):
        return str(f"C:{[x for x in self.client_data]}")

    def __str__(self):
        return str(f"Channel-{self.channel}\tRegion-{self.region}\t{[x for x in self.client_data]}")

    def equal(self, other):
        for i, x in enumerate(self.client_data):
            if x != other.client_data[i]:
                return False
        return True


def load_costumer_data(file_name, chosen_attr=1):
    try:
        customers = []
        with open(file_name) as costumer_file:
            print(f"\nLoading client data... ({file_name})")
            for line in costumer_file:
                if line[0] != "#":
                    data_list = list(map(int, line.rstrip('\n').split(",")))  # convert items in list to int
                    costumer = Client([data_list[1 + chosen_attr]])  # get only the specified attribute
                    costumer.channel = data_list[0]
                    costumer.region = data_list[1]
                    customers.append(costumer)
        print(f"Data loading completed: {len(customers)} values\n")
        return customers
    except (FileNotFoundError, FileExistsError) as e:
        print(f"Unable to retrieve data - ({e})")
