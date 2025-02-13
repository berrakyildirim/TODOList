import os
TODO_FILE = "tasks.txt"

def add_task(task): # It saves the task in a file
    with open(TODO_FILE, "a") as file: # Open file to append the task
        file.write(task + "\n")

    print("Task added %s" % task)

def list_tasks(): # It lists the present tasks
    if not os.path.exists(TODO_FILE) or os.stat(TODO_FILE).st_size == 0: # Give a warning
        print("There are no tasks yet")
        return

    with open(TODO_FILE, "r") as file: # Open the file in reading mode
        tasks = file.readlines()

    i = 0
    while len(tasks) > i:
        print("Task %d: %s" % (i + 1, tasks[i]))
        i += 1

def remove_task(task_number): # It removes a task
    if not os.path.exists(TODO_FILE) or os.stat(TODO_FILE).st_size == 0: # Give a warning
        print("There are no tasks yet")
        return

    with open (TODO_FILE, "r") as file:
        tasks = file.readlines()

    if task_number < 1 or task_number > len(tasks): # Invalid task number
        print("Invalid task number")
        return 0

    removed_task = tasks.pop(task_number - 1)
    with open(TODO_FILE, "w") as file: # Open file in write mode
        file.writelines(tasks)

    print("Task removed: %s" % removed_task)

def clear_tasks(): # It clears all the tasks
    open(TODO_FILE, "w").close()
    print("Tasks cleared")

def main():
    while True:
        choice = int(input("1) Add task\n2) List tasks\n3) Remove task\n4) Clear tasks\n5) Exit\n"))
        if choice == 1:
            task = input("Enter a task: ")
            add_task(task)

        elif choice == 2:
            list_tasks()

        elif choice == 3:
            list_tasks()
            number_remove_task =int(input("Enter a task number to remove: "))
            if number_remove_task == 0:
                print("Invalid task number")
            else:
                remove_task(number_remove_task)
                print("Task removed: %s" % number_remove_task)

        elif choice == 4:
            clear_tasks()

        elif choice == 5:
            exit(0)

        else:
            print("Invalid choice")

if __name__ == "__main__":
                main()