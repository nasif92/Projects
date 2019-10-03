package com.example.assignment_1;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;


public class MainActivity extends AppCompatActivity implements View.OnClickListener{
    ListView ride_view;
    boolean ride_empty = true;
    public static ArrayList<ride> rides;
    public static ArrayAdapter<ride> ride_adapter;
    Button add_button, delete_button;
    public static double total_distance;
    public static int index = -1;
    int edited_index;
    TextView distance;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        // the different views and array lists
        ride_view = findViewById(R.id.ride_content);
        rides =new ArrayList<>();
        add_button = (Button) findViewById(R.id.add_button);
        delete_button = (Button) findViewById(R.id.delete_button);
        distance = findViewById(R.id.text);
        add_button.setOnClickListener(this);
        delete_button.setOnClickListener(this);
        ride_adapter = new ride_array_adapter(rides,this);
        ride_view.setAdapter(ride_adapter);

        ride_view.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                index = i;

            }
        });
        ride_view.setOnItemLongClickListener(new AdapterView.OnItemLongClickListener() {
            @Override
            public boolean onItemLongClick(AdapterView<?> adapterView, View view, int i, long l) {
                Intent intent = new Intent(MainActivity.this, ride_adding_activity.class);
                startActivity(intent);
                index = i;
                edited_index = -1;
                return false;
            }
        });

    }

    // onResume always works whenever the user comes back to the main activity or main view
    // it also counts the total distance everytime it comes back
    @Override
    public void onResume(){
        super.onResume();
        ride_adapter = new ride_array_adapter(rides,this);
        ride_view.setAdapter(ride_adapter);
        total_distance = 0;
        int counter = 0;
        while (counter != rides.size()){
                total_distance += rides.get(counter).getDistance();
            counter++;
        }
        if (counter == 0){
            total_distance = 0;

        }
        distance.setText(String.valueOf(total_distance) + " km");
    }

    // onClick works only when any of the buttons are clicked from main activity
    // it also updates the total distance after it's deleted
    public void onClick(View view) {
        if (view.getId() == R.id.add_button) {
            Toast.makeText(this, "Cool!", Toast.LENGTH_SHORT).show();
            Intent intent = new Intent(MainActivity.this, ride_adding_activity.class);
            startActivity(intent);
            ride_empty = false;

        } else if (view.getId() == R.id.delete_button) {
            Toast.makeText(this, "DELETING SELECTED ITEM", Toast.LENGTH_SHORT).show();
            if ((!ride_empty) && (index != -1)) {
                total_distance -= rides.get(index).getDistance();
                rides.remove(index);
                distance.setText(String.valueOf(Math.round(total_distance*100)/100.0) + " km");
                ride_adapter.notifyDataSetChanged();
            }
            else{
                Toast.makeText(this, "NO ITEM SELECTED", Toast.LENGTH_SHORT).show();
            }
            index = -1;
        }
    }
}
