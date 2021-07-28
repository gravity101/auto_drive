import pickle
import numpy as np
import matplotlib.pyplot as plt

if __name__ == '__main__':
    with open("path.pkl", "rb") as f:
        path = pickle.load(f)

    # draw path
    
    
    # draw heading angle
    plt.plot(path['yaw'])
    plt.show()
