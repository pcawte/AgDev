#ifndef _ERRNO_H
#define _ERRNO_H

#define EPERM       	1   	/* permission error */
#define EINVAL      	2   	/* invalid argument */
#define EIO         	3   	/* io error */
#define EDOM        	4   	/* math domain error */
#define ERANGE      	5   	/* math range error */

// Additional error codes added from set in gnu.org

#define ENOENT			6		// No such directory or directory - file does not exist
#define E2BIG			7		// Argument list too long.
#define EBADF			8		// Bad file descriptor
#define ENOMEM			9		// Cannot allocate memory
#define EACCES			10		// “Permission denied.” The file permissions do not allow
#define EFAULT 			11		// “Bad address.” An invalid pointer was detected. 
#define EEXIST			12		// “File exists.” An existing file was specified in a context where it only makes sense to specify a new file.
#define ENOTDIR 		13		// “Not a directory.” A file that isn’t a directory was specified when a directory is required.
#define EISDIR 			14		// “Is a directory.” You cannot open a directory for writing, or create or remove hard links to it.
#define EMFILE 			15		// “Too many open files.” The current process has too many files open and can’t open any more. Duplicate descriptors do count toward this limit.
#define EOPNOTSUPP		16		// The operation you requested is not supported. Some socket functions don’t make sense for all types of sockets, and others may not be implemented for all communications protocols. On GNU/Hurd systems, this error can happen for many calls when the object does not support the particular operation; it is a generic indication that the server knows nothing to do for that call.

extern int errno;

#endif /* _ERRNO_H */


/* Error codes from gnu.org - a subset taken from these

Macro: int EPERM
“Operation not permitted.” Only the owner of the file (or other resource) or processes with special privileges can perform the operation.

Macro: int ENOENT
“No such file or directory.” This is a “file doesn’t exist” error for ordinary files that are referenced in contexts where they are expected to already exist.

Macro: int ESRCH
“No such process.” No process matches the specified process ID.

Macro: int EINTR
“Interrupted system call.” An asynchronous signal occurred and prevented completion of the call. When this happens, you should try the call again.

You can choose to have functions resume after a signal that is handled, rather than failing with EINTR; see Primitives Interrupted by Signals.

Macro: int EIO
“Input/output error.” Usually used for physical read or write errors.

Macro: int ENXIO
“No such device or address.” The system tried to use the device represented by a file you specified, and it couldn’t find the device. This can mean that the device file was installed incorrectly, or that the physical device is missing or not correctly attached to the computer.

Macro: int E2BIG
“Argument list too long.” Used when the arguments passed to a new program being executed with one of the exec functions (see Executing a File) occupy too much memory space. This condition never arises on GNU/Hurd systems.

Macro: int ENOEXEC
“Exec format error.” Invalid executable file format. This condition is detected by the exec functions; see Executing a File.

Macro: int EBADF
“Bad file descriptor.” For example, I/O on a descriptor that has been closed or reading from a descriptor open only for writing (or vice versa).

Macro: int ECHILD
“No child processes.” This error happens on operations that are supposed to manipulate child processes, when there aren’t any processes to manipulate.

Macro: int EDEADLK
“Resource deadlock avoided.” Allocating a system resource would have resulted in a deadlock situation. The system does not guarantee that it will notice all such situations. This error means you got lucky and the system noticed; it might just hang. See File Locks, for an example.

Macro: int ENOMEM
“Cannot allocate memory.” The system cannot allocate more virtual memory because its capacity is full.

Macro: int EACCES
“Permission denied.” The file permissions do not allow the attempted operation.

Macro: int EFAULT
“Bad address.” An invalid pointer was detected. On GNU/Hurd systems, this error never happens; you get a signal instead.

Macro: int ENOTBLK
“Block device required.” A file that isn’t a block special file was given in a situation that requires one. For example, trying to mount an ordinary file as a file system in Unix gives this error.

Macro: int EBUSY
“Device or resource busy.” A system resource that can’t be shared is already in use. For example, if you try to delete a file that is the root of a currently mounted filesystem, you get this error.

Macro: int EEXIST
“File exists.” An existing file was specified in a context where it only makes sense to specify a new file.

Macro: int EXDEV
“Invalid cross-device link.” An attempt to make an improper link across file systems was detected. This happens not only when you use link (see Hard Links) but also when you rename a file with rename (see Renaming Files).

Macro: int ENODEV
“No such device.” The wrong type of device was given to a function that expects a particular sort of device.

Macro: int ENOTDIR
“Not a directory.” A file that isn’t a directory was specified when a directory is required.

Macro: int EISDIR
“Is a directory.” You cannot open a directory for writing, or create or remove hard links to it.

Macro: int EINVAL
“Invalid argument.” This is used to indicate various kinds of problems with passing the wrong argument to a library function.

Macro: int EMFILE
“Too many open files.” The current process has too many files open and can’t open any more. Duplicate descriptors do count toward this limit.

In BSD and GNU, the number of open files is controlled by a resource limit that can usually be increased. If you get this error, you might want to increase the RLIMIT_NOFILE limit or make it unlimited; see Limiting Resource Usage.

Macro: int ENFILE
“Too many open files in system.” There are too many distinct file openings in the entire system. Note that any number of linked channels count as just one file opening; see Linked Channels. This error never occurs on GNU/Hurd systems.

Macro: int ENOTTY
“Inappropriate ioctl for device.” Inappropriate I/O control operation, such as trying to set terminal modes on an ordinary file.

Macro: int ETXTBSY
“Text file busy.” An attempt to execute a file that is currently open for writing, or write to a file that is currently being executed. Often using a debugger to run a program is considered having it open for writing and will cause this error. (The name stands for “text file busy”.) This is not an error on GNU/Hurd systems; the text is copied as necessary.

Macro: int EFBIG
“File too large.” The size of a file would be larger than allowed by the system.

Macro: int ENOSPC
“No space left on device.” Write operation on a file failed because the disk is full.

Macro: int ESPIPE
“Illegal seek.” Invalid seek operation (such as on a pipe).

Macro: int EROFS
“Read-only file system.” An attempt was made to modify something on a read-only file system.

Macro: int EMLINK
“Too many links.” The link count of a single file would become too large. rename can cause this error if the file being renamed already has as many links as it can take (see Renaming Files).

Macro: int EPIPE
“Broken pipe.” There is no process reading from the other end of a pipe. Every library function that returns this error code also generates a SIGPIPE signal; this signal terminates the program if not handled or blocked. Thus, your program will never actually see EPIPE unless it has handled or blocked SIGPIPE.

Macro: int EDOM
“Numerical argument out of domain.” Used by mathematical functions when an argument value does not fall into the domain over which the function is defined.

Macro: int ERANGE
“Numerical result out of range.” Used by mathematical functions when the result value is not representable because of overflow or underflow.

Macro: int EAGAIN
“Resource temporarily unavailable.” The call might work if you try again later. The macro EWOULDBLOCK is another name for EAGAIN; they are always the same in the GNU C Library.

This error can happen in a few different situations:

An operation that would block was attempted on an object that has non-blocking mode selected. Trying the same operation again will block until some external condition makes it possible to read, write, or connect (whatever the operation). You can use select to find out when the operation will be possible; see Waiting for Input or Output.
Portability Note: In many older Unix systems, this condition was indicated by EWOULDBLOCK, which was a distinct error code different from EAGAIN. To make your program portable, you should check for both codes and treat them the same.

A temporary resource shortage made an operation impossible. fork can return this error. It indicates that the shortage is expected to pass, so your program can try the call again later and it may succeed. It is probably a good idea to delay for a few seconds before trying it again, to allow time for other processes to release scarce resources. Such shortages are usually fairly serious and affect the whole system, so usually an interactive program should report the error to the user and return to its command loop.
Macro: int EWOULDBLOCK
“Operation would block.” In the GNU C Library, this is another name for EAGAIN (above). The values are always the same, on every operating system.

C libraries in many older Unix systems have EWOULDBLOCK as a separate error code.

Macro: int EINPROGRESS
“Operation now in progress.” An operation that cannot complete immediately was initiated on an object that has non-blocking mode selected. Some functions that must always block (such as connect; see Making a Connection) never return EAGAIN. Instead, they return EINPROGRESS to indicate that the operation has begun and will take some time. Attempts to manipulate the object before the call completes return EALREADY. You can use the select function to find out when the pending operation has completed; see Waiting for Input or Output.

Macro: int EALREADY
“Operation already in progress.” An operation is already in progress on an object that has non-blocking mode selected.

Macro: int ENOTSOCK
“Socket operation on non-socket.” A file that isn’t a socket was specified when a socket is required.

Macro: int EMSGSIZE
“Message too long.” The size of a message sent on a socket was larger than the supported maximum size.

Macro: int EPROTOTYPE
“Protocol wrong type for socket.” The socket type does not support the requested communications protocol.

Macro: int ENOPROTOOPT
“Protocol not available.” You specified a socket option that doesn’t make sense for the particular protocol being used by the socket. See Socket Options.

Macro: int EPROTONOSUPPORT
“Protocol not supported.” The socket domain does not support the requested communications protocol (perhaps because the requested protocol is completely invalid). See Creating a Socket.

Macro: int ESOCKTNOSUPPORT
“Socket type not supported.” The socket type is not supported.

Macro: int EOPNOTSUPP
“Operation not supported.” The operation you requested is not supported. Some socket functions don’t make sense for all types of sockets, and others may not be implemented for all communications protocols. On GNU/Hurd systems, this error can happen for many calls when the object does not support the particular operation; it is a generic indication that the server knows nothing to do for that call.

Macro: int EPFNOSUPPORT
“Protocol family not supported.” The socket communications protocol family you requested is not supported.

Macro: int EAFNOSUPPORT
“Address family not supported by protocol.” The address family specified for a socket is not supported; it is inconsistent with the protocol being used on the socket. See Sockets.

Macro: int EADDRINUSE
“Address already in use.” The requested socket address is already in use. See Socket Addresses.

Macro: int EADDRNOTAVAIL
“Cannot assign requested address.” The requested socket address is not available; for example, you tried to give a socket a name that doesn’t match the local host name. See Socket Addresses.

Macro: int ENETDOWN
“Network is down.” A socket operation failed because the network was down.

Macro: int ENETUNREACH
“Network is unreachable.” A socket operation failed because the subnet containing the remote host was unreachable.

Macro: int ENETRESET
“Network dropped connection on reset.” A network connection was reset because the remote host crashed.

Macro: int ECONNABORTED
“Software caused connection abort.” A network connection was aborted locally.

Macro: int ECONNRESET
“Connection reset by peer.” A network connection was closed for reasons outside the control of the local host, such as by the remote machine rebooting or an unrecoverable protocol violation.

Macro: int ENOBUFS
“No buffer space available.” The kernel’s buffers for I/O operations are all in use. In GNU, this error is always synonymous with ENOMEM; you may get one or the other from network operations.

Macro: int EISCONN
“Transport endpoint is already connected.” You tried to connect a socket that is already connected. See Making a Connection.

Macro: int ENOTCONN
“Transport endpoint is not connected.” The socket is not connected to anything. You get this error when you try to transmit data over a socket, without first specifying a destination for the data. For a connectionless socket (for datagram protocols, such as UDP), you get EDESTADDRREQ instead.

Macro: int EDESTADDRREQ
“Destination address required.” No default destination address was set for the socket. You get this error when you try to transmit data over a connectionless socket, without first specifying a destination for the data with connect.

Macro: int ESHUTDOWN
“Cannot send after transport endpoint shutdown.” The socket has already been shut down.

Macro: int ETOOMANYREFS
“Too many references: cannot splice.”

Macro: int ETIMEDOUT
“Connection timed out.” A socket operation with a specified timeout received no response during the timeout period.

Macro: int ECONNREFUSED
“Connection refused.” A remote host refused to allow the network connection (typically because it is not running the requested service).

Macro: int ELOOP
“Too many levels of symbolic links.” Too many levels of symbolic links were encountered in looking up a file name. This often indicates a cycle of symbolic links.

Macro: int ENAMETOOLONG
“File name too long.” Filename too long (longer than PATH_MAX; see Limits on File System Capacity) or host name too long (in gethostname or sethostname; see Host Identification).

Macro: int EHOSTDOWN
“Host is down.” The remote host for a requested network connection is down.

Macro: int EHOSTUNREACH
“No route to host.” The remote host for a requested network connection is not reachable.

Macro: int ENOTEMPTY
“Directory not empty.” Directory not empty, where an empty directory was expected. Typically, this error occurs when you are trying to delete a directory.

Macro: int EPROCLIM
“Too many processes.” This means that the per-user limit on new process would be exceeded by an attempted fork. See Limiting Resource Usage, for details on the RLIMIT_NPROC limit.

Macro: int EUSERS
“Too many users.” The file quota system is confused because there are too many users.

Macro: int EDQUOT
“Disk quota exceeded.” The user’s disk quota was exceeded.

Macro: int ESTALE
“Stale file handle.” This indicates an internal confusion in the file system which is due to file system rearrangements on the server host for NFS file systems or corruption in other file systems. Repairing this condition usually requires unmounting, possibly repairing and remounting the file system.

Macro: int EREMOTE
“Object is remote.” An attempt was made to NFS-mount a remote file system with a file name that already specifies an NFS-mounted file. (This is an error on some operating systems, but we expect it to work properly on GNU/Hurd systems, making this error code impossible.)

Macro: int EBADRPC
“RPC struct is bad.”

Macro: int ERPCMISMATCH
“RPC version wrong.”

Macro: int EPROGUNAVAIL
“RPC program not available.”

Macro: int EPROGMISMATCH
“RPC program version wrong.”

Macro: int EPROCUNAVAIL
“RPC bad procedure for program.”

Macro: int ENOLCK
“No locks available.” This is used by the file locking facilities; see File Locks. This error is never generated by GNU/Hurd systems, but it can result from an operation to an NFS server running another operating system.

Macro: int EFTYPE
“Inappropriate file type or format.” The file was the wrong type for the operation, or a data file had the wrong format.

On some systems chmod returns this error if you try to set the sticky bit on a non-directory file; see Assigning File Permissions.

Macro: int EAUTH
“Authentication error.”

Macro: int ENEEDAUTH
“Need authenticator.”

Macro: int ENOSYS
“Function not implemented.” This indicates that the function called is not implemented at all, either in the C library itself or in the operating system. When you get this error, you can be sure that this particular function will always fail with ENOSYS unless you install a new version of the C library or the operating system.

Macro: int ELIBEXEC
“Cannot exec a shared library directly.”

Macro: int ENOTSUP
“Not supported.” A function returns this error when certain parameter values are valid, but the functionality they request is not available. This can mean that the function does not implement a particular command or option value or flag bit at all. For functions that operate on some object given in a parameter, such as a file descriptor or a port, it might instead mean that only that specific object (file descriptor, port, etc.) is unable to support the other parameters given; different file descriptors might support different ranges of parameter values.

If the entire function is not available at all in the implementation, it returns ENOSYS instead.

Macro: int EILSEQ
“Invalid or incomplete multibyte or wide character.” While decoding a multibyte character the function came along an invalid or an incomplete sequence of bytes or the given wide character is invalid.

Macro: int EBACKGROUND
“Inappropriate operation for background process.” On GNU/Hurd systems, servers supporting the term protocol return this error for certain operations when the caller is not in the foreground process group of the terminal. Users do not usually see this error because functions such as read and write translate it into a SIGTTIN or SIGTTOU signal. See Job Control, for information on process groups and these signals.

Macro: int EDIED
“Translator died.” On GNU/Hurd systems, opening a file returns this error when the file is translated by a program and the translator program dies while starting up, before it has connected to the file.

Macro: int ED
“?.” The experienced user will know what is wrong.

Macro: int EGREGIOUS
“You really blew it this time.” You did what?

Macro: int EIEIO
“Computer bought the farm.” Go home and have a glass of warm, dairy-fresh milk.

Macro: int EGRATUITOUS
“Gratuitous error.” This error code has no purpose.

Macro: int EBADMSG
“Bad message.”

Macro: int EIDRM
“Identifier removed.”

Macro: int EMULTIHOP
“Multihop attempted.”

Macro: int ENODATA
“No data available.”

Macro: int ENOLINK
“Link has been severed.”

Macro: int ENOMSG
“No message of desired type.”

Macro: int ENOSR
“Out of streams resources.”

Macro: int ENOSTR
“Device not a stream.”

Macro: int EOVERFLOW
“Value too large for defined data type.”

Macro: int EPROTO
“Protocol error.”

Macro: int ETIME
“Timer expired.”

Macro: int ECANCELED
“Operation canceled.” An asynchronous operation was canceled before it completed. See Perform I/O Operations in Parallel. When you call aio_cancel, the normal result is for the operations affected to complete with this error; see Cancellation of AIO Operations.

Macro: int EOWNERDEAD
“Owner died.”

Macro: int ENOTRECOVERABLE
“State not recoverable.”

The following error codes are defined by the Linux/i386 kernel. They are not yet documented.

Macro: int ERESTART
“Interrupted system call should be restarted.”

Macro: int ECHRNG
“Channel number out of range.”

Macro: int EL2NSYNC
“Level 2 not synchronized.”

Macro: int EL3HLT
“Level 3 halted.”

Macro: int EL3RST
“Level 3 reset.”

Macro: int ELNRNG
“Link number out of range.”

Macro: int EUNATCH
“Protocol driver not attached.”

Macro: int ENOCSI
“No CSI structure available.”

Macro: int EL2HLT
“Level 2 halted.”

Macro: int EBADE
“Invalid exchange.”

Macro: int EBADR
“Invalid request descriptor.”

Macro: int EXFULL
“Exchange full.”

Macro: int ENOANO
“No anode.”

Macro: int EBADRQC
“Invalid request code.”

Macro: int EBADSLT
“Invalid slot.”

Macro: int EDEADLOCK
“File locking deadlock error.”

Macro: int EBFONT
“Bad font file format.”

Macro: int ENONET
“Machine is not on the network.”

Macro: int ENOPKG
“Package not installed.”

Macro: int EADV
“Advertise error.”

Macro: int ESRMNT
“Srmount error.”

Macro: int ECOMM
“Communication error on send.”

Macro: int EDOTDOT
“RFS specific error.”

Macro: int ENOTUNIQ
“Name not unique on network.”

Macro: int EBADFD
“File descriptor in bad state.”

Macro: int EREMCHG
“Remote address changed.”

Macro: int ELIBACC
“Can not access a needed shared library.”

Macro: int ELIBBAD
“Accessing a corrupted shared library.”

Macro: int ELIBSCN
“.lib section in a.out corrupted.”

Macro: int ELIBMAX
“Attempting to link in too many shared libraries.”

Macro: int ESTRPIPE
“Streams pipe error.”

Macro: int EUCLEAN
“Structure needs cleaning.”

Macro: int ENOTNAM
“Not a XENIX named type file.”

Macro: int ENAVAIL
“No XENIX semaphores available.”

Macro: int EISNAM
“Is a named type file.”

Macro: int EREMOTEIO
“Remote I/O error.”

Macro: int ENOMEDIUM
“No medium found.”

Macro: int EMEDIUMTYPE
“Wrong medium type.”

Macro: int ENOKEY
“Required key not available.”

Macro: int EKEYEXPIRED
“Key has expired.”

Macro: int EKEYREVOKED
“Key has been revoked.”

Macro: int EKEYREJECTED
“Key was rejected by service.”

Macro: int ERFKILL
“Operation not possible due to RF-kill.”

Macro: int EHWPOISON
“Memory page has hardware error.”

*/