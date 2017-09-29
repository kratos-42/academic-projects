package packetcounter;


import java.awt.Color;
import java.awt.BasicStroke;
import java.text.SimpleDateFormat;
import java.util.Date;

import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.DateAxis;
import org.jfree.data.time.RegularTimePeriod;
import org.jfree.data.xy.XYDataset;
import org.jfree.ui.ApplicationFrame;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.renderer.xy.XYLineAndShapeRenderer;
import org.jfree.data.time.Millisecond;
import org.jfree.data.time.TimeSeries;
import org.jfree.data.time.TimeSeriesCollection;

public class Grafico extends ApplicationFrame {

    TimeSeries in = new TimeSeries("IN");
    TimeSeries out = new TimeSeries("OUT");

    public Grafico(String applicationTitle, String chartTitle) {
        super(applicationTitle);
        JFreeChart xylineChart = ChartFactory.createTimeSeriesChart(
                chartTitle,
                "Data",
                "Nº Pacotes",
                createDataset(),

                true, true, false);

        ChartPanel chartPanel = new ChartPanel(xylineChart);
        chartPanel.setPreferredSize(new java.awt.Dimension(560, 367));

        final XYPlot grafico = (XYPlot) xylineChart.getPlot();
        XYLineAndShapeRenderer renderer = new XYLineAndShapeRenderer();
        renderer.setSeriesPaint(0, Color.MAGENTA);
        renderer.setSeriesPaint(1, Color.cyan);
        renderer.setSeriesStroke(0, new BasicStroke(4.0f));
        renderer.setSeriesStroke(1, new BasicStroke(3.0f));
        grafico.setRenderer(renderer);
        setContentPane(chartPanel);

        DateAxis axis = (DateAxis) grafico.getDomainAxis();
        axis.setDateFormatOverride(new SimpleDateFormat("kk:mm:ss"));
    }

    public TimeSeriesCollection createDataset() {

        TimeSeriesCollection dataset = new TimeSeriesCollection();
        dataset.addSeries(in);
        dataset.addSeries(out);

        return dataset;
    }

    public TimeSeries getIn(){
        return this.in;
    }

    public TimeSeries getOut(){
        return this.out;
    }


    void atualizarIn(RegularTimePeriod tempo , int diff) {
        in.add(tempo,diff);
    }
    void atualizarOut(RegularTimePeriod tempo , int diff) {
        out.add(tempo,diff);
    }
}