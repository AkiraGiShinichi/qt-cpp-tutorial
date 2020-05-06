# https://medium.com/swlh/python-gui-with-pyqt-pyside2-5cca38d739fa
import sys
from PySide2.QtWidgets import *
from PySide2.QtCore import *
from PySide2.QtGui import *
import cv2
import qimage2ndarray


class MyWidget(QWidget):
    def __init__(self):
        QWidget.__init__(self)

        # OPENCV
        cap = cv2.VideoCapture(0)
        cap.set(cv2.CAP_PROP_FRAME_WIDTH, 320)
        cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 240)

        # timer for getting frames
        timer = QTimer()
        timer.timeout.connect(self.displayFrame)
        timer.start(1)

        label = QLabel('No Camera Feed')
        button = QPushButton("Quiter")
        button.clicked.connect(sys.exit)  # quiter button

        self.layout = QVBoxLayout()
        self.layout.addWidget(button)
        self.layout.addWidget(label)
        self.setLayout(self.layout)

    def displayFrame(self):
        ret, frame = cap.read()
        frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        image = qimage2ndarray.array2qimage(frame)
        self.label.setPixmap(QPixmap.fromImage(image))


if __name__ == "__main__":
    app = QApplication(sys.argv)

    widget = MyWidget()
    widget.resize(800, 600)
    widget.show()

    sys.exit(app.exec_())