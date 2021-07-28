import rosbag
import pickle
import tf
import math
from tf.transformations import euler_from_quaternion


from geometry_msgs.msg import PoseStamped

if __name__ == '__main__':
    bag = rosbag.Bag("bag-file-path.bag")
    path = {'x': [], 'y': [], 'yaw': [] 's': []}
    
    x1 = 0 y1 = 0
    for topic, msg, t in bag.read_messages(topics=['/ego_pose']):
        x = msg.pose.orientation.x
        y = msg.pose.orientation.y
	path['s'] = math.hypot(x-x1, y-y1)
	path['x'].append(msg.pose.position.x)
	path['y'].append(msg.pose.position.y)
	x1, y1 = x, y
        z = msg.pose.orientation.z
        w = msg.pose.orientation.w
        (roll,pitch,yaw)=euler_from_quaternion((x,y,z,w))
	roll = math.degrees(roll)
        pitch = math.degrees(pitch)
        yaw = math.degrees(yaw)
        path['yaw'].append(yaw)

    with open("path.pkl", "wb") as f:
        pickle.dump(path, f)
