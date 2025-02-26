import time
import socket
from concurrent.futures import ThreadPoolExecutor, as_completed

# Server address and port
SERVER_HOST = "127.0.0.1"
SERVER_PORT = 8080
FILE_PATH = "path/to/input.txt"

# Number of concurrent connections and total requests
CONCURRENT_CONNECTIONS = 50
TOTAL_REQUESTS = 500

def make_request(server_host, server_port, file_path):
    """Make a single TCP request to the server."""
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((server_host, server_port))
            s.sendall((file_path + "\n").encode())  # Ensure newline

            start_time = time.perf_counter()
            response = b""
            
            while True:
                chunk = s.recv(4096)
                if not chunk:
                    break
                response += chunk  # Accumulate response
            
            elapsed = time.perf_counter() - start_time
            return len(response) > 0, elapsed
    except (socket.error, socket.timeout) as e:
        return False, str(e)

def benchmark(server_host, server_port, file_path, concurrent_connections, total_requests):
    """Benchmark the TCP server with concurrent connections."""
    times = []
    errors = 0
    start_time = time.perf_counter()

    with ThreadPoolExecutor(max_workers=concurrent_connections) as executor:
        futures = [executor.submit(make_request, server_host, server_port, file_path) for _ in range(total_requests)]

        for future in as_completed(futures):
            success, elapsed = future.result()
            if success:
                times.append(elapsed)
            else:
                errors += 1

    total_time = time.perf_counter() - start_time
    
    # Results
    print(f"Total Requests: {total_requests}")
    print(f"Concurrent Connections: {concurrent_connections}")
    print(f"Total Time: {total_time:.2f} seconds")
    print(f"Requests per Second: {total_requests / total_time:.2f}")
    print(f"Average Latency: {sum(times) / len(times) if times else 0:.4f} seconds")
    print(f"Error Rate: {errors / total_requests * 100:.2f}%")

if __name__ == "__main__":
    benchmark(SERVER_HOST, SERVER_PORT, FILE_PATH, CONCURRENT_CONNECTIONS, TOTAL_REQUESTS)
