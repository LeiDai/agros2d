from libcpp.vector cimport vector
from libcpp.map cimport map
from libcpp.pair cimport pair
from libcpp cimport bool

cdef extern from "limits.h":
    int c_INT_MIN "INT_MIN"
    int c_INT_MAX "INT_MAX"
    int c_DOUBLE_MIN "DOUBLE_MIN"
    int c_DOUBLE_MAX "DOUBLE_MAX"

cdef extern from "../../src/pythonlab/pygeometry.h":
    cdef cppclass PyGeometry:
        PyGeometry()

        void activate()

        void addNode(double, double) except +
        void addEdge(double, double, double, double, double, map[char*, int], map[char*, char*]) except +
        void addEdgeByNodes(int, int, double, map[char*, int], map[char*, char*]) except +
        void addLabel(double, double, double, map[char*, int], map[char*, int], map[char*, char*]) except +

        void removeNode(int index) except +
        void removeEdge(int index) except +
        void removeLabel(int index) except +

        void removeNodePoint(double, double)
        void removeEdgePoint(double, double, double, double, double)
        void removeLabelPoint(double, double)

        void selectNodes(vector[int]) except +
        void selectEdges(vector[int]) except +
        void selectLabels(vector[int]) except +

        void selectNodePoint(double, double)
        void selectEdgePoint(double, double)
        void selectLabelPoint(double, double)

        void selectNone()

        void moveSelection(double, double, bool)
        void rotateSelection(double, double, double, bool)
        void scaleSelection(double, double, double, bool)
        void removeSelection()

        void mesh()
        char *meshFileName() except +

        void zoomBestFit()
        void zoomIn()
        void zoomOut()
        void zoomRegion(double, double, double, double)

cdef class __Geometry__:
    cdef PyGeometry *thisptr

    # Geometry()
    def __cinit__(self):
        self.thisptr = new PyGeometry()
    def __dealloc__(self):
        del self.thisptr

    def activate(self):
        self.thisptr.activate()

    # add_node(x, y)
    def add_node(self, double x, double y):
        self.thisptr.addNode(x, y)

    # remove_node(index)
    def remove_node(self, int index):
        self.thisptr.removeNode(index)

    # add_edge(x1, y1, x2, y2, angle, refinements, boundaries)
    def add_edge(self, double x1, double y1, double x2, double y2, double angle = 0.0, refinements = {}, boundaries = {}):

        cdef map[char*, int] refinements_map
        cdef pair[char*, int] refinement
        for key in refinements:
            refinement.first = key
            refinement.second = refinements[key]
            refinements_map.insert(refinement)

        cdef map[char*, char*] boundaries_map
        cdef pair[char*, char *] boundary
        for key in boundaries:
            boundary.first = key
            boundary.second = boundaries[key]
            boundaries_map.insert(boundary)

        self.thisptr.addEdge(x1, y1, x2, y2, angle, refinements_map, boundaries_map)

    # add_edge_by_nodes(start_node_index, end_node_index, angle, refinements, boundaries)
    def add_edge_by_nodes(self, int start_node_index, int end_node_index, double angle = 0.0, refinements = {}, boundaries = {}):

        cdef map[char*, int] refinements_map
        cdef pair[char*, int] refinement
        for key in refinements:
            refinement.first = key
            refinement.second = refinements[key]
            refinements_map.insert(refinement)

        cdef map[char*, char*] boundaries_map
        cdef pair[char*, char *] boundary
        for key in boundaries:
            boundary.first = key
            boundary.second = boundaries[key]
            boundaries_map.insert(boundary)

        self.thisptr.addEdgeByNodes(start_node_index, end_node_index, angle, refinements_map, boundaries_map)

    # remove_edge(index)
    def remove_edge(self, int index):
        self.thisptr.removeEdge(index)

    # add_label(x, y, area, refinements, orders, materials)
    def add_label(self, double x, double y, double area = 0.0, refinements = {}, orders = {}, materials = {}):

        cdef map[char*, int] refinements_map
        cdef pair[char*, int] refinement
        for key in refinements:
            refinement.first = key
            refinement.second = refinements[key]
            refinements_map.insert(refinement)

        cdef map[char*, int] orders_map
        cdef pair[char*, int] order
        for key in orders:
            order.first = key
            order.second = orders[key]
            orders_map.insert(order)

        cdef map[char*, char*] materials_map
        cdef pair[char*, char *] material
        for key in materials:
            material.first = key
            material.second = materials[key]
            materials_map.insert(material)

        self.thisptr.addLabel(x, y, area, refinements_map, orders_map, materials_map)

    # remove_label(index)
    def remove_label(self, int index):
        self.thisptr.removeLabel(index)

    # remove_node_point(x, y)
    def remove_node_point(self, double x, double y):
        self.thisptr.removeNodePoint(x, y)

    # remove_edge_point(x1, y1, x2, y2, angle)
    def remove_edge_point(self, double x1, double y1, double x2, double y2, double angle):
        self.thisptr.removeEdgePoint(x1, y1, x2, y2, angle)

    # remove_label_point(x, y)
    def remove_label_point(self, double x, double y):
        self.thisptr.removeLabelPoint(x, y)

    # select_nodes(nodes)
    def select_nodes(self, nodes = []):
        cdef vector[int] nodes_vector
        for i in nodes:
            nodes_vector.push_back(i)

        self.thisptr.selectNodes(nodes_vector)

    # select_edges(edges)
    def select_edges(self, edges = []):
        cdef vector[int] edges_vector
        for i in edges:
            edges_vector.push_back(i)

        self.thisptr.selectEdges(edges_vector)

    # select_labels(labels)
    def select_labels(self, labels = []):
        cdef vector[int] labels_vector
        for i in labels:
            labels_vector.push_back(i)

        self.thisptr.selectLabels(labels_vector)

    # select_node_point(x, y)
    def select_node_point(self, double x, double y):
        self.thisptr.selectNodePoint(x, y)

    # select_edge_point(x, y)
    def select_edge_point(self, double x, double y):
        self.thisptr.selectEdgePoint(x, y)

    # select_label_point(x, y)
    def select_label_point(self, double x, double y):
        self.thisptr.selectLabelPoint(x, y)


    # move_selection(dx, dy, copy)
    def move_selection(self, double dx, double dy, int copy = False):
        self.thisptr.moveSelection(dx, dy, int(copy))

    # rotate_selection(x, y, angle, copy)
    def rotate_selection(self, double x, double y, double angle, int copy = False):
        self.thisptr.rotateSelection(x, y, angle, int(copy))

    # scale_selection(x, y, scale, copy)
    def scale_selection(self, double x, double y, double scale, int copy = False):
        self.thisptr.scaleSelection(x, y, scale, int(copy))

    # remove_selection(dx, dy, copy)
    def remove_selection(self):
        self.thisptr.removeSelection()

    # select_none()
    def select_none(self):
        self.thisptr.selectNone()

    # mesh()
    def mesh(self):
        self.thisptr.mesh()

    # mesh_file_name()
    def mesh_file_name(self):
        self.thisptr.meshFileName()

    # zoom_best_fit()
    def zoom_best_fit(self):
        self.thisptr.zoomBestFit()

    # zoom_in()
    def zoom_in(self):
        self.thisptr.zoomIn()

    # zoom_out()
    def zoom_out(self):
        self.thisptr.zoomOut()

    # zoom_region()
    def zoom_region(self, double x1, double y1, double x2, double y2):
        self.thisptr.zoomRegion(x1, y1, x2, y2)

geometry = __Geometry__()