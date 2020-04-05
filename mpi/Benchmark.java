/*
Author: Joshua DeNio
Date: 08/09/2019
Description: This program benchmarks matrix multiplication in Java
*/
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.io.File;
import java.io.FileInputStream;
import java.io.BufferedInputStream;
import java.io.FileReader;
import java.util.Scanner;
import java.util.Arrays;
import java.lang.System;
import java.util.concurrent.TimeUnit;
import java.util.Date;
import java.text.DecimalFormat;

public class Benchmark {
    public static void main(String[] args) throws FileNotFoundException, IOException 
    {
        
        int row = 100;
        int col = 100;
        double[][] mat_double = new double[row][col];
        double[][] mat_double2 = new double[row][col];
        double[][] mat_double_output = new double[row][col];

        //FileInputStream fis = new FileInputStream("100x100_matrix.txt");
        //BufferedInputStream bis = new BufferedInputStream(fis);

        //double buf[];
        //int i = 0;
        //int content;
        //int row_iter = 0;
        //int col_iter = 0;
        //while ((content = bis.read()) != -1)
        //{
            //System.out.print((char) content);
            //mat_double[row_iter][col_iter] = (double) content;
            //if (col_iter % 100 == 0)
            //{
            //    row_iter++;
            //    col_iter = 0;
            //}
            //col_iter++;
        //}
        //System.out.println(Arrays.deepToString(mat_double));

        //for (int r = 0; r < row; r++)
        //    
        //    for (int c = 0; c < col; c++)
        //    {
        //        mat_double[r][c] = buf[iterator];
        //        iterator++;
        //    }       

        //fis.close();

        Scanner sc = new Scanner(new BufferedReader(new FileReader("100x100_matrix.txt")));
        while(sc.hasNextLine()) {
         for (int i=0; i<mat_double.length; i++) {
            String[] line = sc.nextLine().trim().split(" ");
            for (int j=0; j<line.length; j++) {
               mat_double[i][j] = Double.parseDouble(line[j]);
               mat_double2[i][j] = Double.parseDouble(line[j]);
               mat_double_output[i][j] = 0;
            }
         }
        }
        //print_mat(mat_double, 100, 100);


        DecimalFormat df = new DecimalFormat("#0.00000000");

        //long result = TimeUnit.SECONDS.convert(elapsedTime, TimeUnit.NANOSECONDS);

        //System.out.println("StartTime: " + startTime);
        //System.out.println("EndTime: " + endTime);
        //print_mat(mat_double_output, 100, 100);
        //System.out.println("Time taken 100x100 multiplication (Double): " + df.format((endTime - startTime)/1000) + " seconds");

        for (int i = 0; i < 100; i++)
        {
            long startTime = System.currentTimeMillis();
            mat_mult_double(mat_double, mat_double2, mat_double_output);
            long endTime = System.currentTimeMillis();
            long elapsedTime = endTime - startTime;
            System.out.println(df.format((endTime - startTime)/1000.0) + " seconds");
        }
    }

    public static void mat_mult_double(double[][] mat1, double[][] mat2, double[][] output_mat_double)
    {
        //row = mat1.length;
        //col = mat1[0].length;
        int row = 100;
        int col = 100;
        for (int r = 0; r < row; r++)
            for (int c = 0; c < col; c++)
                for (int r_iter = 0; r_iter < row; r_iter++)
                    output_mat_double[r][c] += mat1[r][r_iter] * mat2[r_iter][c];
       
    }

    public static void print_mat (double[][] mat, int row, int col ) 
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
                System.out.println(mat[i][j]);
            System.out.println();
        }    
                
    }

 }
