
public class Main {
    public static void main(String[] args) {
        int n=9;
        boolean resultado=false;
        for(int i=2;i<n;i++){
            if(n%i==0){
                resultado=false;
                break;
            }else{
                resultado=true;
            }
           }
        if(resultado==true){
            System.out.println("Es primo");
           }else{
            System.out.println("No es primo");
           }
    }
}