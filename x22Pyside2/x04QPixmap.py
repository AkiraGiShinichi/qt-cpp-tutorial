# https://medium.com/swlh/python-gui-with-pyqt-pyside2-5cca38d739fa
import sys
from PySide2.QtWidgets import *
from PySide2.QtGui import QPixmap

class MyWidget(QWidget):
    def __init__(self):
        QWidget.__init__(self)

        # Add a Label:
        label = QLabel()

        # Add a pixmap instance to the label:
        label.setPixmap(QPixmap("junzi.jpg"))

        self.layout = QVBoxLayout()
        self.layout.addWidget(label)
        self.setLayout(self.layout)


if __name__ == "__main__":
    app = QApplication(sys.argv)

    widget = MyWidget()
    widget.resize(800, 600)
    widget.show()

    sys.exit(app.exec_())