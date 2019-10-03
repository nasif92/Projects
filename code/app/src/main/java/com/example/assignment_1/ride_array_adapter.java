package com.example.assignment_1;

import android.content.Context;
import android.icu.text.Transliterator;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import java.util.ArrayList;

public class ride_array_adapter extends ArrayAdapter<ride> {
    private ArrayList<ride> rides;
    private Context context;

    public ride_array_adapter(ArrayList<ride> rides, Context context) {
        super(context, 0,rides);
        this.rides = rides;
        this.context = context;
    }

    public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
        View view =convertView;
        if (view == null) {
            view = LayoutInflater.from(context).inflate(R.layout.content, parent, false);
        }
        ride some_ride =rides.get(position);
        TextView date = view.findViewById(R.id.date_text);
        TextView time = view.findViewById(R.id.time_text);
        TextView distance = view.findViewById(R.id.distance_text);
        date.setText(some_ride.getDate());
        time.setText(some_ride.getTime());
        distance.setText(String.valueOf(some_ride.getDistance()) + " km");

        return view;
    }
}
