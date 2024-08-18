using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bai1
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("Nhap n: ");
            int n = int.Parse(Console.ReadLine());
            Console.Write("Nhap k: ");
            int k = int.Parse(Console.ReadLine());

            int ketQua = TinhToHop_DP_CaiTien(n, k);
            Console.WriteLine("To hop chap {0} cua {1} la: {2}", k, n, ketQua);
            Console.ReadLine();
        }

        static int TinhToHop_DP_CaiTien(int n, int k) 
        {
            int[] V = new int[n + 1]; 
            int p1, p2;

            V[0] = 1;
            V[1] = 1;

            for (int i = 2; i <= n; i++)
            {
                p1 = V[0];
                for (int j = 1; j < i; j++)
                {
                    p2 = V[j];
                    V[j] = p1 + p2;
                    p1 = p2;
                }
                V[i] = 1;
            }

            return V[k];
        }
    }
}
