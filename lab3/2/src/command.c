#include <coder.h>
#include <error.h>

int encode_file(const char* in_file_name, const char* out_file_name)
{
    FILE* in = fopen(in_file_name, "rb");
    if (!in) {
        error_output(__FILE__, __func__, __LINE__ - 1);
        return error;
    }
    FILE* out = fopen(out_file_name, "wb");
    if (!out) {
        error_output(__FILE__, __func__, __LINE__ - 1);
        fclose(in);
        return error;
    }

    uint32_t code_point;
    CodeUnit* code_unit = (CodeUnit*)malloc(sizeof(CodeUnit));
    if (!code_unit) {
        error_output(__FILE__, __func__, __LINE__ - 1);
        fclose(in);
        fclose(out);
        return error;
    }

    while (1) {
        if (fscanf(in, "%" SCNx32, &code_point) != 1) {
            if (feof(in)) {
                fclose(in);
                fclose(out);
                free(code_unit);
                return success;
            }
            error_output(__FILE__, __func__, __LINE__ - 1);
            fclose(in);
            fclose(out);
            free(code_unit);
            return error;
        }
        if (encode(code_point, code_unit)) {
            error_output(__FILE__, __func__, __LINE__ - 1);
            fclose(in);
            fclose(out);
            free(code_unit);
            return error;
        }
        if (write_code_unit(out, code_unit)) {
            error_output(__FILE__, __func__, __LINE__ - 1);
            fclose(in);
            fclose(out);
            free(code_unit);
            return error;
        }
    }
    fclose(in);
    fclose(out);
    free(code_unit);
    return success;
}

int decode_file(const char* in_file_name, const char* out_file_name)
{
    FILE* in = fopen(in_file_name, "rb");
    if (!in) {
        error_output(__FILE__, __func__, __LINE__ - 1);
        return error;
    }
    FILE* out = fopen(out_file_name, "wb");
    if (!out) {
        error_output(__FILE__, __func__, __LINE__ - 1);
        fclose(in);
        return error;
    }

    uint32_t code_point;
    CodeUnit* code_unit = (CodeUnit*)malloc(sizeof(CodeUnit));
    if (!code_unit) {
        error_output(__FILE__, __func__, __LINE__ - 1);
        fclose(in);
        fclose(out);
        return error;
    }
    while (1) {
        if (read_next_code_unit(in, code_unit)) {
            if (feof(in)) {
                fclose(in);
                fclose(out);
                free(code_unit);
                return success;
            }
            error_output(__FILE__, __func__, __LINE__ - 1);
            fclose(in);
            fclose(out);
            free(code_unit);
            return error;
        }
        code_point = decode(code_unit);
        fprintf(out, "%" PRIx32 "\n", code_point);
    }
    fclose(in);
    fclose(out);
    free(code_unit);
    return success;
}