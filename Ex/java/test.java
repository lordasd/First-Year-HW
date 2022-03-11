import java.util.Scanner;

public class test{
    
    public static void main(String[] args){ 
        int factorialn = 1, factorialr = 1, factorialn_r = 1;
        int mone, mehane;

        Scanner obj = new Scanner(System.in);
        int n = obj.nextInt();
        int r = obj.nextInt();

        factorialn = factorial(factorialn, n);
        factorialr = factorial(factorialr, r);
        factorialn_r = factorial(factorialn_r, n-r);

        mone = factorialn;
        mehane = factorialr*factorialn_r;

        System.out.println(mone/mehane);

    }

    static int factorial(int input, int lim){
        for(int i = 2; i <= lim; i++){
            input *= i;
        }
        return input;
    }
}