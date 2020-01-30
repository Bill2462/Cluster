/**
 * @file displayFeatures.cpp
 * @brief This source file contains code for displaying features on the graph. 
 * @author Krzysztof Adamkiewicz
 * @date 29/1/2020
 */

// This file is a part of Cluster - Application for image clustering.
// Copyright (C) 2020 Krzysztof Adamkiewicz <kadamkiewicz835@gmail.com>
// 
// This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "utils/utils.hpp"
#include <algorithm>
#include <cmath>

/**
 * @brief Display reduced features on the screen.
 */
void MainWindow::displayFeatures()
{
    QVector<double> x(features.size()), y(features.size());
    for(size_t i=0; i<features.size(); i++)
    {
        x[i] = features[i].featureVector[0];
        y[i] = features[i].featureVector[1];
    }

    
    //build marker
    QCPScatterStyle myScatter;
    myScatter.setShape(QCPScatterStyle::ssCircle);
    myScatter.setPen(QPen(Qt::red));
    myScatter.setBrush(Qt::red);
    myScatter.setSize(10);
    
    //plot
    ui->graph->addGraph();
    ui->graph->graph(0)->setData(x, y);
    ui->graph->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->graph->graph(0)->setScatterStyle(myScatter);
    
    //determine and set intervals for plots
    double minX = *std::min_element(x.constBegin(), x.constEnd());
    double maxX = *std::max_element(x.constBegin(), x.constEnd());
    
    double minY = *std::min_element(y.constBegin(), y.constEnd());
    double maxY = *std::max_element(y.constBegin(), y.constEnd());
    
    ui->graph->xAxis->setRange(minX-abs(minX*0.2), maxX+abs(maxX*0.2));
    ui->graph->yAxis->setRange(minY-abs(minY*0.2), maxY+abs(maxY*0.2));
    ui->graph->replot();
}
