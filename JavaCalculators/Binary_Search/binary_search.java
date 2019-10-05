public class binary_search {
	public static int return_index(int number, int[] array) {
		int mid = (array.length/2) - 1;
		int right = array.length;
		int left = 0;
		int index = 0;
		if ((number < array[0]) || (number > array[array.length - 1])) {
			index = -1;
		}
		else {
			index = -1;
			while (left != right){
				if ( array[mid] == number) {
					index = mid;
					return index;
				}
				else if (array[mid] > number) {
					right = mid;
					mid = (left + right - 1)/2;
				}
				else if (array[mid] < number) {
					left = mid + 1;
					mid = (left + right - 1)/2;
				}
					
			}
		}

		return index;
	}
	
	public static void main(String[] args) {
		long start = System.nanoTime();
		int[] arr = {1,2,3,4,5,6,7,8,9,10};
		int[] arr2 = {2,3,4,6,7,8,9,12,14,34,35,40,45,55,65,66,100,1012,10021,12414,13456};
		int index = return_index(9, arr);
		int index2 = return_index(10022,arr2);
		if (index != -1)
			System.out.println("Index: " + index);
		else {
			System.out.println("Index not found");

		}
		if (index2 != -1)
			System.out.println("Index: " + index2);
		else {
			System.out.println("Index not found");

		}
		long end   = System.nanoTime();
		long time = end - start;
		System.out.println("Total time needed: " + time);
			
	}
}