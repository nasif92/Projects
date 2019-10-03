package com.example.assignment_1;

public class ride {
    private String date;
    private String time;
    private double distance,speed;
    private int cadence;
    private String comments;


    // the constructor having the primary three elements
    ride(String date, String time, double distance){
        this.date = date;
        this.time = time;
        this.distance = distance;

    }

    // constructor having all attributes
    ride(String time, double distance, double speed, int cadence, String comments){
        this.time = time;
        this.distance = distance;
        this.speed = speed;
        this.cadence = cadence;
        this.comments = comments;
    }

    // the getters and setters

    public String getDate() {
        return date;
    }

    public void setDate(String date) {
        this.date = date;
    }

    public String getTime() {
        return time;
    }

    public void setTime(String time) {
        this.time = time;
    }

    public double getDistance() {
        return distance;
    }

    public void setDistance(double distance) {
        this.distance = distance;
    }

    public double getSpeed() {
        return speed;
    }

    public void setSpeed(double speed) {
        this.speed = speed;
    }

    public int getCadence() {
        return cadence;
    }

    public void setCadence(int cadence) {
        this.cadence = cadence;
    }

    public String getComments() {
        return comments;
    }

    public void setComments(String comments) {
        this.comments = comments;
    }
}
