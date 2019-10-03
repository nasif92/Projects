package com.example.assignment_1;

import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.DialogFragment;

import android.app.DatePickerDialog;
import android.app.TimePickerDialog;
import android.content.Intent;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.TimePicker;
import android.widget.Toast;


import java.text.DateFormat;
import java.text.SimpleDateFormat;

import static com.example.assignment_1.MainActivity.index;
import java.util.Calendar;
import java.util.Date;

import static com.example.assignment_1.MainActivity.rides;
import static java.util.Objects.isNull;

public class ride_adding_activity extends AppCompatActivity implements View.OnClickListener, TimePickerDialog.OnTimeSetListener{

    public boolean button_clicked = false;
    boolean edited = false;
    EditText speed_input, distance_input,cadence_input,comments_input;
    TextView date_input, time_input;
    boolean allGood;
    boolean cadence_bool = true;
    boolean speed_bool = true;
    boolean comment_bool = true;
    Button button;
    Double distance;
    String speed,cadence,comments,some_day, some_time;
    private DatePickerDialog.OnDateSetListener mDateSetListener;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        DateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
        DateFormat timeFormat = new SimpleDateFormat("HH:MM");
        Date test_date = Calendar.getInstance().getTime();
        some_day = dateFormat.format(test_date);
        some_time = timeFormat.format(test_date);
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ride_adding_activity);
        // Get the Intent that started this activity and extract the string
        final Intent intent = getIntent();


        // Capture the layout's TextView and set the string as its text
        TextView time_inst = findViewById(R.id.time_inst);

        //sending activity to main after button is pushed every view by ID is here
        // all the id's are here
        button = (Button) findViewById(R.id.button);
        date_input = (TextView) findViewById(R.id.date);
        date_input.setText(some_day);
        time_input = findViewById(R.id.time);
        time_input.setText(some_time);
        distance_input = findViewById(R.id.distance_text);
        speed_input = findViewById(R.id.average_speed);
        cadence_input = findViewById(R.id.cadence);
        comments_input = findViewById(R.id.comments);
        button.setOnClickListener(this);


        // only while editing the index is given to me due to long click
        if (index != -1 ){
            date_input.setText(rides.get(index).getDate());
            time_input.setText(rides.get(index).getTime());
            distance_input.setText(String.valueOf(rides.get(index).getDistance()));
            if (!isNull(rides.get(index).getSpeed())){
                speed_input.setText(String.valueOf(rides.get(index).getSpeed()));
            }
            if (rides.get(index).getCadence() != 0){
                cadence_input.setText(String.valueOf(rides.get(index).getCadence()));
            }
            if(!isNull(rides.get(index).getComments())){
                comments_input.setText(rides.get(index).getComments());
            }
            edited = true;
        }


        // working on the time picker
        time_input.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                DialogFragment timePicker = new time_picker();
                timePicker.show(getSupportFragmentManager(), "time picker");
            }

        });

        // working on the date picker
        date_input.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Calendar cal = Calendar.getInstance();
                int year = cal.get(Calendar.YEAR);
                int month = cal.get(Calendar.MONTH);
                int day = cal.get(Calendar.DAY_OF_MONTH);
                DatePickerDialog dialog = new DatePickerDialog(
                        ride_adding_activity.this,android.R.style.Theme_Holo_Light_Dialog_MinWidth,
                        mDateSetListener,
                        year,month,day);
                dialog.getWindow().setBackgroundDrawable(new ColorDrawable(Color.TRANSPARENT));
                dialog.show();
            }
        });
        // date picker format
        mDateSetListener = new DatePickerDialog.OnDateSetListener() {
            @Override
            public void onDateSet(DatePicker datePicker, int year, int month, int day) {
                month = month + 1;

                date_input.setText(String.format("%02d-%02d-%02d",year,month,day));
            }
        };
    }

    // format of the time picker
    @Override
    public void onTimeSet(TimePicker view, int hourOfDay, int minute) {
        time_input.setText(String.format("%02d:%02d",hourOfDay,minute));
    }

    // onClick works only when the confirm button is clicked.
    // it checks the errors and also sends the user to main activity after taking all the inputs
    @Override
    public void onClick(View v) {
        ride test_ride;
        if (v.getId() == R.id.button){
            button_clicked = true;
            Intent intent1 = new Intent(ride_adding_activity.this, MainActivity.class);
            String time = time_input.getText().toString();
            String date = date_input.getText().toString();
            if (String.valueOf(distance).matches("")){
                Toast.makeText(getApplicationContext(),"NO DISTANCE INPUT", Toast.LENGTH_SHORT).show();
            }
            else{

                // error checking distance, speed cadence and comments
                // for checking distance
                try{
                    if(Double.valueOf(distance_input.getText().toString()) < 0.0){
                        Toast.makeText(getApplicationContext(),"DISTANCE FORMAT WRONG", Toast.LENGTH_SHORT).show();
                    }
                    else{
                        distance = Double.valueOf(distance_input.getText().toString());
                        allGood = true;
                    }

                }catch (Exception ex) {
                    Toast.makeText(getApplicationContext(),"MISSING MANDATORY ARGUMENT: DISTANCE", Toast.LENGTH_SHORT).show();
                    allGood = false;
                }
                try{
                    // creating the object with mandatory arguments
                    ride new_ride = new ride(date, time,distance);

                    // checking if optional arguments are given
                    // checking speed input
                    if(!speed_input.getText().toString().isEmpty() ){
                        speed = speed_input.getText().toString();
                        if (Double.valueOf(speed) < 0.0){
                            speed_bool = false;
                            allGood = false;
                        }
                        else{
                            speed_bool = true;
                            allGood = true;
                        }
                        new_ride.setSpeed(Double.valueOf(speed));
                    }

                    // checking cadence input
                    if(!cadence_input.getText().toString().isEmpty()){
                        cadence = cadence_input.getText().toString();
                        if (Integer.valueOf(cadence) < 0){
                            cadence_bool = false;
                            allGood = false;
                        }
                        else {
                            cadence_bool = true;
                            allGood = true;
                        }
                        new_ride.setCadence(Integer.valueOf(cadence));
                    }

                    // checking comments input
                    if(!comments_input.getText().toString().isEmpty()){
                        comments = comments_input.getText().toString();
                        if (comments.length() > 20){
                            comment_bool = false;
                            allGood = false;

                        }
                        else {
                            comment_bool = true;
                            allGood = true;
                        }
                        new_ride.setComments(comments);
                    }
                    // if both edited and all errors are checked
                    if((edited) && (allGood)){
                        rides.remove(index);
                        MainActivity.rides.add(index,new_ride);
                    }
                    // only if new rides are added
                    else if (allGood){
                        rides.add(new_ride);
                    }

                }catch (Exception e) {
                    Toast.makeText(getApplicationContext(), "ARGUMENT FORMAT WRONG", Toast.LENGTH_SHORT).show();
                    allGood = false;
                }
                if (comment_bool == false){
                    Toast.makeText(getApplicationContext(), "COMMENTS TOO LONG", Toast.LENGTH_SHORT).show();
                    allGood = false;

                }
                if( speed_bool == false){
                    Toast.makeText(getApplicationContext(), "SPEED FORMAT WRONG", Toast.LENGTH_SHORT).show();
                    allGood = false;
                }
                if( cadence_bool == false){
                    Toast.makeText(getApplicationContext(), "CADENCE FORMAT WRONG", Toast.LENGTH_SHORT).show();
                    allGood = false;

                }
                if (allGood){
                    index = -1;
                    finish();
                }
                else{
                    Toast.makeText(getApplicationContext(), "ARGUMENT FORMAT WRONG", Toast.LENGTH_SHORT).show();
                    Toast.makeText(getApplicationContext(), "MAKE SURE THERE ARE NO NON NEGATIVE INTEGERS", Toast.LENGTH_SHORT).show();

                }
            }
        }
    }
}
