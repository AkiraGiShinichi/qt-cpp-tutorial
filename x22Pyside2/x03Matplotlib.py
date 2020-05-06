# https://medium.com/swlh/python-gui-with-pyqt-pyside2-5cca38d739fa
import sys
from PySide2.QtWidgets import *
from matplotlib.figure import Figure
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas

class MyWidget(QWidget):
    def __init__(self):
        QWidget.__init__(self)

        # generate the plot
        fig = Figure(figsize=(600, 600), dpi=72, facecolor=(1, 1, 1), edgecolor=(0, 0, 0))
        ax = fig.add_subplot(111)
        # Add data:
        ax.plot([0, 1])
        # generate the canvas to display the plot
        canvas = FigureCanvas(fig)

        # Add a button
        button = QPushButton("I'm still just a button man")
        button.setMaximumWidth(200)

        self.layout = QVBoxLayout()
        self.layout.addWidget(button)
        self.layout.addWidget(canvas)
        self.setLayout(self.layout)


if __name__ == "__main__":
    app = QApplication(sys.argv)

    widget = MyWidget()
    widget.resize(800, 600)
    widget.show()

    sys.exit(app.exec_())