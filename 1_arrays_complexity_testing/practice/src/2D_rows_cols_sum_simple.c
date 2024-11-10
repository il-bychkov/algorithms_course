#include <stdio.h>
#include <stdint.h>

#define N_MAX 500
#define M_MAX 500

int main() 
{
	int n, m;
	scanf("%d", &n);
	scanf("%d", &m);
	
	// The most simple way is to allocate a big array, read all the number and then compute + print
	int64_t arr[N_MAX][M_MAX];
	
	// Two arrays to store our sums	
	int64_t sum_rows[N_MAX] = {0};
	int64_t sum_cols[M_MAX] = {0};		
	
	// Read the input array
	for(int i = 0; i < n; i++)	
	{
        for(int j = 0; j < m; j++)				
		{
            // lld - long long decimal IS IMPORTANT
			scanf("%lld", &arr[i][j]);	
		}
	}
	
	// Now traverse the array and compute all the sums
    for(int i = 0; i < n; i++)
	{
        for(int j = 0; j < m; j++)
		{	            
			sum_rows[i] += arr[i][j];
			sum_cols[j] += arr[i][j];            
        }
    }
	
    // Then just print the results

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
