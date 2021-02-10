""" This program is under the terms of GNU Affero General Public License.
    See LICENSE file for more detail.
"""

from tkinter import *
import math

# Constants
SCREEN_SIZE = 1000
VERTEX_COLOR = "#969696"
VERTEX_RADIUS = 15
VERTEX_WIDTH = 3
EDGE_COLOR = "#646464"
EDGE_WIDTH = 4
TEXT_FONT = "Arial 9"

def application():
    global graph
    global tk, canvas
    global rotation, dis, screen_center
    
    graph = []

    '''rotation = 0
    dis = 0
    screen_center = 0'''
    
    tk = Tk()
    tk.title("city-traffic")
    tk.geometry(str(SCREEN_SIZE) + "x" + str(SCREEN_SIZE))
    canvas = Canvas(tk, height=SCREEN_SIZE, width=SCREEN_SIZE)
    
    test_run()
    print(dis)
    while True:
        canvas.pack()
        tk.update()

# Basic Concepts. Cars are not considered yet
def draw_vertex(x, y, index):
    canvas.create_oval(x-VERTEX_RADIUS, y-VERTEX_RADIUS,
                       x+VERTEX_RADIUS, y+VERTEX_RADIUS,
                       width=VERTEX_WIDTH, fill=VERTEX_COLOR)
    canvas.create_text(x, y, text=str(index), font=TEXT_FONT)

def connect_vertices(vertex1, vertex2, length):
    line = canvas.create_line(*get_vertex_pos(vertex1),
                              *get_vertex_pos(vertex2),
                              width=EDGE_WIDTH)
    canvas.tag_lower(line);

def read_graph(filename):
    pass

def input_graph():
    pass

def draw_graph(vert_count, center_dis):
    global rotation, dis, screen_center
    rotation = 2 * math.pi / vert_count
    dis = center_dis
    screen_center = SCREEN_SIZE / 2
    for i in range(0, vert_count):
        draw_vertex(*get_vertex_pos(i), i)

def get_vertex_pos(vert_index):
    return (screen_center+dis*math.cos(rotation*vert_index),
            screen_center+dis*math.sin(rotation*vert_index))

def test_run():
    draw_graph(45, 450)
    connect_vertices(1, 36, 1)
    connect_vertices(4, 12, 1)
    connect_vertices(13, 23, 1)
    connect_vertices(1, 2, 1)
    connect_vertices(19, 41, 1)

application();
