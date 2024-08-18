using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bai2
{
    class DoVat 
    {
        public string Ten;
        public int TrongLuong;
        public int GiaTri;
        public int PhuongAn;

        public DoVat(string ten, int trongLuong, int giaTri)
        {
            Ten = ten;
            TrongLuong = trongLuong;
            GiaTri = giaTri;
            PhuongAn = 0;
        }
    }

    class Program
    {
        const int MAX = 100;

        static void TaoBang(DoVat[] dsVat, int n, int W, int[,] F, int[,] X) 
            
            for (int v = 0; v <= W; v++)
            {
                X[1, v] = v / dsVat[1].TrongLuong;
                F[1, v] = X[1, v] * dsVat[1].GiaTri;
            }

            
            for (int k = 2; k <= n; k++)
            {
                for (int v = 0; v <= W; v++)
                {
                    int FMax = F[k - 1, v];
                    int XMax = 0;
                    int yk = v / dsVat[k].TrongLuong;

                    for (int xk = 1; xk <= yk; xk++)
                    {
                        if (F[k - 1, v - xk * dsVat[k].TrongLuong] + xk * dsVat[k].GiaTri > FMax)
                        {
                            FMax = F[k - 1, v - xk * dsVat[k].TrongLuong] + xk * dsVat[k].GiaTri;
                            XMax = xk;
                        }
                    }

                    F[k, v] = FMax;
                    X[k, v] = XMax;
                }
            }
        }

        static void TraBang(DoVat[] dsVat, int n, int W, int[,] F, int[,] X) 
        {
            Console.WriteLine("\nPhuong an toi uu:");
            int v = W;
            for (int k = n; k >= 1; k--)
            {
                if (X[k, v] > 0)
                {
                    dsVat[k].PhuongAn = X[k, v];
                    v -= X[k, v] * dsVat[k].TrongLuong;
                }
            }

            int tongGiaTri = 0; 
            int tongTrongLuong = 0;

            for (int i = 1; i <= n; i++)
            {
                if (dsVat[i].PhuongAn > 0)
                {
                    Console.WriteLine("{0}: {1}", dsVat[i].Ten, dsVat[i].PhuongAn);
                    tongGiaTri += dsVat[i].PhuongAn * dsVat[i].GiaTri;
                    tongTrongLuong += dsVat[i].PhuongAn * dsVat[i].TrongLuong;
                }
            }

            Console.WriteLine("Tong gia tri: {0}", tongGiaTri);
            Console.WriteLine("Tong trong luong: {0}", tongTrongLuong);
            Console.ReadLine();
        }

        static void Main(string[] args)
        {
            Console.Write("Nhap so luong do vat: ");
            int n = int.Parse(Console.ReadLine());

            Console.Write("Nhap trong luong toi da cua balo: ");
            int W = int.Parse(Console.ReadLine());

            DoVat[] dsVat = new DoVat[n + 1];

            for (int i = 1; i <= n; i++)
            {
                Console.WriteLine("Nhap thong tin do vat thu {0}:", i);
                Console.Write("Ten: ");
                string ten = Console.ReadLine();
                Console.Write("Trong luong: ");
                int trongLuong = int.Parse(Console.ReadLine());
                Console.Write("Gia tri: ");
                int giaTri = int.Parse(Console.ReadLine());

                dsVat[i] = new DoVat(ten, trongLuong, giaTri);
            }

            int[,] F = new int[n + 1, W + 1];
            int[,] X = new int[n + 1, W + 1];

            TaoBang(dsVat, n, W, F, X);
            TraBang(dsVat, n, W, F, X);
        }
    }
}