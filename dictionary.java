import java.util.Scanner;

//******THE CLASS *******//
class dictionary{
	int Id;
	String Name;
	int number;
	Scanner input = new Scanner(System.in);
	public int askUser(){
		System.out.print("How many people do you want?: ");
		number = input.nextInt();
		return number;
	}
	
	public String getName(){
		System.out.print("Enter Name: ");
		String name = input.next();
		return name;
	}
	public void setName(String name){
		Name = name;
	}
	
	public int getId(){
		System.out.print("ID?: ");
		int number = input.nextInt();
		return number;
	}

	public void setId(int someID){
		Id = someID;
	}

	public int askForId(){
		System.out.print("Which ID would you like to view?: ");
		Scanner input = new Scanner(System.in);
		int Id = input.nextInt();
		return Id;
	}

	// ****** THE MAIN *****//
	public static void main(String[] args){
		dictionary someDictionary = new dictionary();
		int num = someDictionary.askUser();
		System.out.println("You are making a list for " + num + " people");
		dictionary[] people = new dictionary[num];

		// getting names and Id for the number of people
		for (int i=0; i< num; i++){
			people[i] = new dictionary();
			String some_name = people[i].getName();
			int some_Id = people[i].getId();
			if ((some_name == "0" ) || ( some_Id == 0)){
				System.out.print("Are you sure you want to check everyone on the list?(Y/N) ");
				Scanner input = new Scanner(System.in);
				String this_Input = input.next();
				if (this_Input == "y"){
					
				}
			}
			//decorations
			for ( int j=0; j< 20; j++){
				System.out.print("=");
			}
			System.out.println();
			people[i].setName(some_name);
			people[i].setId(some_Id);
		}
		System.out.println();


		// some modifications
		dictionary newDictionary = new dictionary();
		int some_Id = newDictionary.askForId();

		// printing the person with Id
		while(some_Id != 0){
			for ( int i=0; i < num; i++){
				if (some_Id == people[i].Id){
					System.out.println("The person is: " + people[i].Name);
				}
			}
			//decorations
			for ( int i=0; i< 20; i++){
				System.out.print("=");
			}
			System.out.println();	
			some_Id = newDictionary.askForId();

		}
		System.out.print("Alright Goodbye!");
		
	}
}