""" This program is under the terms of GNU Affero General Public License.
    See LICENSE file for more detail.
"""

from tkinter import *

# Constants
SCREEN_SIZE = 600
VERTEX_RADIUS = 30
EDGE_THICKNESS = 2
VERTEX_COLOR = "#969696"
EDGE_COLOR = (100, 100, 100)
TEXT_COLOR = (0, 0, 0)
TEXT_FONT = "Arial 18"

graph = []

tk = Tk()
tk.title("city-traffic")
tk.geometry(str(SCREEN_SIZE) + "x" + str(SCREEN_SIZE))
canvas = Canvas(tk, height=600, width=600)


# Basic Concepts. Cars are not considered yet
def draw_vertex(x, y, index):
    vertex_index = canvas.create_oval(x-VERTEX_RADIUS, y-VERTEX_RADIUS,
                                      x+VERTEX_RADIUS, y+VERTEX_RADIUS,
                                      width=3, fill=VERTEX_COLOR)
    canvas.create_text(x, y, text=str(index), font=TEXT_FONT)

def connect_vertices(vertex1, vertex2, length):
    pass

def read_graph(filename):
    pass

def input_graph():
    pass

def draw_graph():
    pass

draw_vertex(300, 300, 16)
while True:
    canvas.pack()
    tk.update()
