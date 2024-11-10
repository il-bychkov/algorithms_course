#include <stdio.h>
#include <stdint.h>

#define N_MAX 500
#define M_MAX 500

int main() 
{
	int n, m;
	scanf("%d", &n);
	scanf("%d", &m);
	
	// Two arrays to store our sums
	
	int64_t sum_rows[N_MAX] = {0};
	int64_t sum_cols[M_MAX] = {0};
   
    // This algorithm does one single pass over all elements
	int64_t temp;
    for(int i = 0; i < n; i++)
	{
        for(int j = 0; j < m; j++)
		{		
            // Scanf current number and store it in int64_t variable. lld - long long decimal IS IMPORTANT	
			scanf("%lld", &temp);
			sum_rows[i] += temp;
			sum_cols[j] += temp;            
        }
    }
	
    // Now just print all the sums computed

    printf("\n");
	
    for(int i = 0; i < n; i++) {
		// lld - long long decimal IS IMPORTANT	
        printf("%lld ", sum_rows[i]);
    }
    printf("\n");
    
    for(int i = 0; i < m; i++) {
		// lld - long long decimal IS IMPORTANT	
        printf("%lld ", sum_cols[i]);
    }
    printf("\n");

    return 0;
}
