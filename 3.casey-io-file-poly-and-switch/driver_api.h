
enum FileDriverOperationType {
  OP_TYPE_none,
  OP_TYPE_open,
  OP_TYPE_read,
  OP_TYPE_write,
  OP_TYPE_close,
  OP_TYPE_get_name,
};
struct FileDriverOperation_open {
  void *f;
  const char *filename;
};
struct FileDriverOperation_read {
  void *f;
  void *data;
  size_t size;
};
struct FileDriverOperation_write {
  void *f;
  void *data;
  size_t size;
};
struct FileDriverOperation_close {
  void *f;
};
struct FileDriverOperation_get_name {
  const char *name;
};
struct FileDriverOperationData {
  FileDriverOperationType type;
  union {
    FileDriverOperation_open open;
    FileDriverOperation_read read;
    FileDriverOperation_write write;
    FileDriverOperation_close close;
    FileDriverOperation_get_name get_name;
  };
};

typedef void FileDriverHandler(FileDriverOperationData *in_out);

typedef FileDriverHandler *GetFileDriverProc();
