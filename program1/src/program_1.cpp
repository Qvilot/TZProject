
#include "../include/program_1.h"

using namespace std;

void SharedBuffer::put(const std::string &data)
{
  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock, [this]()
          { return this->q.empty(); });
  q.push(data);
  cv.notify_one();
}

std::string SharedBuffer::get()
{
  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock, [this]()
          { return !this->q.empty(); });
  std::string data = q.front();
  q.pop();
  cv.notify_one();
  return data;
}

bool SharedBuffer::isEmpty()
{
  std::unique_lock<std::mutex> lock(mtx);
  return q.empty();
}

void thread1_function(SharedBuffer &buffer)
{
  std::string input;
  while (true)
  {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Input string: " << endl;
    std::getline(std::cin, input);
    input.erase(std::remove(input.begin(), input.end(), ' '), input.end());

    if (input.length() > 64 || input.find_first_not_of("0123456789") != std::string::npos)
    {
      std::cerr << "Incorrect: The string must consist of numbers and not exceed 64 characters" << std::endl;
      continue;
    }

    sortAndReplace(input);
    buffer.put(input);
  }
}

void thread2_function(SharedBuffer &buffer, const std::string &serverIP, int serverPort)
{
  int sockfd = -1;
  struct sockaddr_in servaddr;

  std::string data;

  while (true)
  {
    sockfd = -1;
    if (sockfd == -1)
    {
      sockfd = socket(AF_INET, SOCK_STREAM, 0);
      if (sockfd == -1)
      {
        perror("socket");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        continue;
      }

      memset(&servaddr, 0, sizeof(servaddr));
      servaddr.sin_family = AF_INET;
      servaddr.sin_port = htons(serverPort);
      if (inet_pton(AF_INET, serverIP.c_str(), &servaddr.sin_addr) <= 0)
      {
        perror("Invalid address/ Address not supported");
        close(sockfd);
        sockfd = -1;
        continue;
      }

      if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
      {
        perror("connect");
        close(sockfd);
        sockfd = -1;
        continue;
      }
    }

    try
    {
      data = buffer.get();
      long long sum = calculateSum(data);

      std::string string_sum = std::to_string(sum);
      char *str_sum = new char[string_sum.length() + 1];
      strcpy(str_sum, string_sum.c_str());
      if (send(sockfd, str_sum, strlen(str_sum), 0) == -1)
      {
        perror("send");
        close(sockfd);
        sockfd = -1;
        delete[] str_sum;
        continue;
      }
      std::cout << "Processed string: " << data << std::endl;
      std::cout << "Sum: " << sum << std::endl;
      delete[] str_sum;
    }
    catch (const std::exception &e)
    {
      std::cerr << "Error in thread2: " << e.what() << std::endl;
      close(sockfd);
      sockfd = -1;
    }
  }
  close(sockfd);
}

int main()
{
  SharedBuffer buffer;
  std::string serverIP = "127.0.0.1";
  int serverPort = 12345;

  std::thread thread1(thread1_function, std::ref(buffer));
  std::thread thread2(thread2_function, std::ref(buffer), serverIP, serverPort);

  thread1.join();
  thread2.join();

  return 0;
}
