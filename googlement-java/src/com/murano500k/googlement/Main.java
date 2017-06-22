package com.murano500k.googlement;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

import static java.lang.Math.pow;

public class Main {

    public static void main(String[] args) {
	// write your code here
        File in=new File("/home/artem/projects/codejam/googlement-java/A-small-practice.in");
        BufferedReader br=null;
        int iterator=0;
        try {
            br=new BufferedReader(new InputStreamReader(new FileInputStream(in)));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        try {
            if (br != null) {
                while(br.ready()){
                    String data=br.readLine();
                    System.out.println("Case #"+iterator+" in: "+data);
                    int result=process(data);
                    iterator++;

                    System.out.println("Case #"+iterator+" out: "+result);
                }
            }else throw new NullPointerException("br null");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    private static List<Integer> sToL(String in,int size){
        int numDigits=in.length();

        List<Integer>digits=new ArrayList<>(size);

        int i=0;
        for (int j = 0; j <size; j++) {
            digits.set(j,0);
            i++;
        }
        int indexIn=0;
        for (; i <numDigits; i++) {
            digits.set(i,Integer.parseInt(String.valueOf(in.charAt(indexIn++))));
        }
        return digits;
    }
    private static int process(String in) {

        int numDigits=in.length();
        int validParentNum=1;
        int max = (int) pow(10,numDigits)-1;
        List<Integer> digits= sToL(in, numDigits);
        /*for (Integer d :
                digits) {
            System.out.println(""+d);
        }
        return 0;*/

        for (int i = 1; i < max; i++) {
            List<Integer> item=sToL(String.valueOf(i),numDigits);
            if(canDecayInto(item,digits)) validParentNum++;
        }
        return validParentNum;
    }
    private static List<Integer> getChild(List<Integer> digits) {
        int numDigits=digits.size();
        List<Integer> childDigits=new ArrayList<>();
        int sum=0;
        for (int i = 0; i < digits.size(); i++) {
            sum+=digits.get(i);
            for (int j = 1; j < digits.size(); j++) if(digits.get(i)==j) childDigits.add(j, childDigits.get(i)+1);
        }
        if(sum>numDigits)return null;
        else return childDigits;
    }
    private static boolean canDecayInto(List<Integer> g, List<Integer> testG) {
        if (g == null) return false;
        else if(g.equals(testG))return true;
        List<Integer> child=getChild(g);
        if(child==null)return false;
        return  canDecayInto(child,testG);
    }

    public class Googlement{
        List<Integer> digits;

        public Googlement(List<Integer> digits) {
            this.digits = digits;
        }
        public Googlement decay(){
            int size= digits.size();
            int index=0;

            List<Integer> newDigits=new ArrayList<>();
            for (int i = 0; i < size; i++) {
                if(digits.get(i)>0){
                    int entries=digits.get(i);
                    while(entries-->0){
                        newDigits.add(i);
                    }
                }
            }
            return new Googlement(newDigits);
        }
    }
    private static String getChild(String string) {
        int numDigits=string.length();
        List<Integer>digits=new ArrayList<>();
        for (int i = 0; i < numDigits; i++) {
            digits.add(Integer.parseInt(String.valueOf(string.charAt(i))));
        }
        List<Integer> childDigits=new ArrayList<>();
        for (int i = 1; i < numDigits+1; i++) {
            childDigits.add(0);
        }
        int sum=0;
        for (int i = 0; i < digits.size(); i++) {
            sum+=digits.get(i);
            for (int j = 1; j < digits.size(); j++) if(digits.get(i)==j) childDigits.set(j, childDigits.get(i)+1);
        }
        if(sum>numDigits)return null;
        else {
            StringBuilder childS= new StringBuilder();
            for (Integer i :
                    childDigits) {
                childS.append(i);
            }
            return childS.toString();
        }
    }
}