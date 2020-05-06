# https://medium.com/swlh/python-gui-with-pyqt-pyside2-5cca38d739fa
import sys
from random import randint
from PySide2 import QtGui
from PySide2.QtWidgets import *
from PySide2.QtCharts import QtCharts
from PySide2.QtGui import QPainter

class MyWidget(QWidget):
    def __init__(self):
        QWidget.__init__(self)

        # Initialize chart
        chart = QtCharts.QChart()
        lineSeries = QtCharts.QLineSeries()
        # Make some random data points
        dataSeries = [(i + 1, randint(0, 99999)) for i in range(200)]
        # load data into chart:
        for point in dataSeries:
            lineSeries.append(point[0], point[1])
        # Add Some Chart Options
        chart.addSeries(lineSeries)
        chart.setTitle("Random Numbers from 0-9000")
        chart.createDefaultAxes()

        # Create a container (similar to a widget)
        chartView = QtCharts.QChartView(chart)
        chartView.setRenderHint(QPainter.Antialiasing)
        # Some Chart Styling
        lineSeries.setColor(QtGui.QColor("darkgray"))
        chartView.chart().setBackgroundBrush(QtGui.QColor("ivory"))

        self.layout = QVBoxLayout()
        self.layout.addWidget(chartView)
        self.setLayout(self.layout)


if __name__ == "__main__":
    app = QApplication(sys.argv)

    widget = MyWidget()
    widget.resize(800, 600)
    widget.show()

    sys.exit(app.exec_())