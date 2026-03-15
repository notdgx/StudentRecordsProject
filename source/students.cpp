#include "../headers/students.hpp"

int Students::student_rollno_A = 1;
int Students::student_id_A = 1000;

Students::Students() {}

void Students::generate_rollno()
{
}

void Students::generate_student_id()
{
    data.student_id = student_id_A;
    student_id_A++;
}

// ______________________________
// SETTERss
// ______________________________

int Students::set_student_name(const std::string &student_name, int day, int month, int year, const char &student_gender)
{
    int x = validations::validate_name(student_name, sizeof(data.student_name));
    if (x == 1)
    {
        strcpy(data.student_name, student_name.c_str());
    }
    return x;
}

int Students::set_student_dob(int day, int month, int year)
{
    int x = validations::validate_dob(day, month, year);
    if (x == 1)
    {
        data.student_dob.day = day;
        data.student_dob.month = month;
        data.student_dob.year = year;
    }
    return x;
}

int Students::set_student_gender(const char &student_gender)
{
    int x = validations::validate_gender(student_gender);
    if (x == 1)
    {
        data.student_gender = student_gender;
    }
    return x;
}

int Students::set_student_course(const std::string &student_course)
{
    int x = validations::validate_course(student_course, sizeof(data.student_course));
    if (x == 1)
    {
        strcpy(data.student_course, student_course.c_str());
    }
    return x;
}

int Students::set_student_section(const char &student_section)
{
    int x = validations::validate_section(student_section);
    if (x == 1)
    {
        data.student_section = student_section;
    }
    return x;
}

int Students::set_student_number_of_subjects(int student_number_of_subjects)
{
    int x = validations::validate_number_of_subjects(student_number_of_subjects);
    if (x == 1)
    {
        data.student_number_of_subjects = student_number_of_subjects;
    }
    return x;
}

int Students::set_student_enrollement_year(int student_enrollement_year)
{
    int x = validations::validate_enrollement_year(student_enrollement_year);
    if (x == 1)
    {
        data.student_enrollement_year = student_enrollement_year;
    }
    return x;
}

int Students::set_student_pending_fee(int student_pending_fee)
{
    int x = validations::validae_pending_fee(student_pending_fee);
    if (x == 1)
    {
        data.student_pending_fee = student_pending_fee;
    }
    return x;
}

int Students::set_students_contacts_email(const std::string &email)
{
    int x = validations::validate_email(email, sizeof(data.student_contacts.email));
    if (x == 1)
    {
        strcpy(data.student_contacts.email, email.c_str());
    }
    return x;
}

int Students::set_students_contacts_phone_no(const std::string &phone_no)
{
    int x = validations::validate_phone_no(phone_no);
    if (x == 1)
    {
        strcpy(data.student_contacts.phone_no, phone_no.c_str());
    }
    return x;
}

int Students::set_students_contacts_address(
    const std::string &house,
    const std::string &street,
    const std::string &city,
    const std::string &state,
    const std::string &country,
    const std::string &pincode)
{
    int x = validations::validate_address_field(house, sizeof(data.student_address.house));
    int y = validations::validate_address_field(street, sizeof(data.student_address.street));
    int z = validations::validate_address_field(city, sizeof(data.student_address.city));
    int a = validations::validate_address_field(state, sizeof(data.student_address.state));
    int b = validations::validate_address_field(country, sizeof(data.student_address.country));
    int c = validations::validate_address_pincode(pincode);

    if (x == 1 && y == 1 && z == 1 && a == 1 && b == 1 && c == 1)
    {
        strcpy(data.student_address.house, house.c_str());
        strcpy(data.student_address.street, street.c_str());
        strcpy(data.student_address.city, city.c_str());
        strcpy(data.student_address.state, state.c_str());
        strcpy(data.student_address.country, country.c_str());
        strcpy(data.student_address.pincode, pincode.c_str());
        return 1;
    }
    return 0;
}

// ─────────────────────────────────────
//  Getterss
// ─────────────────────────────────────

int Students::get_student_id()
{
    return data.student_id;
}


int Students::get_student_rollno()
{
    return data.student_rollno;
}


std::string Students::get_student_name()
{
    return std::string(data.student_name);
}


datafields::date Students::get_student_dob()
{
    return data.student_dob;
}


char Students::get_student_gender()
{
    return data.student_gender;
}


std::string Students::get_student_course()
{
    return std::string(data.student_course);
}


char Students::get_student_section()
{
    return data.student_section;
}


int Students::get_student_number_of_subjects()
{
    return data.student_number_of_subjects;
}


int Students::get_student_pending_fee()
{
    return data.student_pending_fee;
}


Subject *Students::get_student_subjects()
{
    return data.student_subjects;
}


datafields::contact Students::get_student_contacts()
{
    return data.student_contacts;
}


datafields::address Students::get_student_address()
{
    return data.student_address;
}