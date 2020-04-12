using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net.Http;
using System.Threading.Tasks;

namespace LoadTests
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length < 2)
            {
                Console.WriteLine("Пример запуска:\ndotnet run [URL] [кол-во запросов]");
                return;
            }

            var url = args[0];
            var requestsCount = int.Parse(args[1]);
            if (requestsCount <= 0)
            {
                Console.WriteLine("Число запросов должно быть больше 0!");
                return;
            }

            //var url = "http://localhost:5005";
            //var requestsCount = 100;

            var tasks = new Task<(bool IsSuccess, string Reason)>[requestsCount];

            Console.WriteLine("Тест запущен");
            var timer = new Stopwatch();
            timer.Start();

            for (int i = 0; i < requestsCount; i++)
            {
                tasks[i] = Task.Run(async () => await SendRequest(url));
            }

            Task.WaitAll(tasks);

            timer.Stop();
            var requestsMilliseconds = timer.ElapsedMilliseconds;

            var successfulTasksCount = tasks.Where(x => x.Result.IsSuccess).Count();
            var failedTasksCount = tasks.Where(x => !x.Result.IsSuccess).Count();
            var reasons = tasks.Where(x => !string.IsNullOrEmpty(x.Result.Reason)).Select(x => x.Result.Reason).Distinct();

            Console.WriteLine("\nРезультаты:");
            Console.WriteLine("Общее кол-во запросов: " + requestsCount);
            Console.WriteLine("Кол-во успешных запросов: " + successfulTasksCount
                + " (" + (double)successfulTasksCount * 100 / requestsCount + "%)");
            Console.WriteLine("Кол-во проваленных запросов: " + failedTasksCount
                + " (" + (double)failedTasksCount * 100 / requestsCount + "%)");

            if (reasons.Any())
                Console.WriteLine("Причины:\n - " + string.Join("\n - ", reasons));

            Console.WriteLine("Затраченное время: " + (double)requestsMilliseconds + " мс");
            Console.WriteLine("Среднее время выполнения одного запроса: " + requestsMilliseconds / (double)requestsCount + " мс");

            Console.ReadKey();
        }

        private static async Task<(bool IsSuccess, string Reason)> SendRequest(string url)
        {
            using (var httpClient = new HttpClient())
            {
                httpClient.Timeout = TimeSpan.FromSeconds(180);
                try
                {
                    var response = await httpClient.GetAsync(url);
                    if (response.IsSuccessStatusCode)
                        return (IsSuccess: true, Reason: null);
                    else
                        return (IsSuccess: false, Reason: response.ReasonPhrase);
                }
                catch (Exception ex)
                {
                    var exception = ex;
                    while (exception.InnerException != null)
                        exception = exception.InnerException;

                    return (IsSuccess: false, Reason: exception.Message);
                }
            }
        }
    }
}
