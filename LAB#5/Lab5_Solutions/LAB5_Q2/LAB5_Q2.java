package LAB5_Q2;
import java.util.HashMap;
import java.util.Scanner;

class LAB5_Q2 {
    public static void main(String[] args) {
        //      product           id     date
        HashMap<String, HashMap<String, String>> DragonCorporation = new HashMap<String, HashMap<String, String>>();
        Scanner sc = new Scanner(System.in);
        int counter = 1;
        for (int i = 0; i < 5; i++) {
            String product = sc.nextLine();
            String date = sc.nextLine();
            // put leading zeros to create the id
            String id = new String(new char[3-String.valueOf(counter).length()]).replace("\0", "0")+String.valueOf(counter);
            if(DragonCorporation.get(product) == null) DragonCorporation.put(product, new HashMap<String, String>());
            DragonCorporation.get(product).put(id, date);
            counter++;
        }
        sc.close();
        // print
        for(String product : DragonCorporation.keySet()) {
            System.out.println("\"" + product + "\"");
            for(String id : DragonCorporation.get(product).keySet()) {
                System.out.println(id + " - " + DragonCorporation.get(product).get(id));
            }
        }
        
    }
}